#! /usr/bin/env perl
package inic;
use strict;
use warnings;

my $CDEBUG = 0;

my $regexp = {
    structBegin => '^\s*struct\s+(\w+)',
    structEnd   => '^\s*\}\s*;\s*$',
    iniKeyEnd   => '^\s*END_INI_KEY',
    itemDefine  => '^\s*(\S+)\s*(\*?)\s*(\w+)\s*(=\s*(\S+))?\s*;',
    defaultVal  => '\s*=\s*[^;]+',
    emptyLine   => '^\s*$',
    commentLine => '^\s*//',
};

my $structName = undef;
my $fieldList = []; # [{type, name, isPointer, defaultVal}]
my $keyEndFlag = 0;
my $indent = '    '; # 4 space

while (<>) {
    chomp;
    my $line = $_;
    # next if $line =~ $regexp->{emptyLine};
    # next if $line =~ $regexp->{commentLine};
    # print "$line\n" if $CDEBUG;

    if ($line =~ $regexp->{emptyLine} || $line =~ $regexp->{commentLine}) {
	# pass; no action
    }
    elsif ($line =~ $regexp->{structBegin}) {
        $structName = $1;
        $fieldList = [];
        $keyEndFlag = 0;
        print "// found struct $structName\n" if $CDEBUG;
    }
    elsif ($line =~ $regexp->{iniKeyEnd}) {
        $keyEndFlag = 1;
        print "$line\n"; # also preserve this line
        print "// found END_INI_KEY lable\n" if $CDEBUG;
    }
    elsif (!$keyEndFlag && $line =~ $regexp->{itemDefine}) {
        my $type = $1;
        my $isPointer = $2;
        my $name = $3;
        my $hasDefault = $4;
        my $defaultVal = $5 // '';
	if ($type =~ '\*$') {
	    # type* , pointer * is joined with type
	    $type =~ s/\*$//;
	    $isPointer = '*';
	}
        push(@$fieldList, {
                type => $type,
                name => $name,
                isPointer => $isPointer,
                defaultVal => $defaultVal,
            });
        $line =~ s/$regexp->{defaultVal}//;
        print "// found key[$name] of type[$type], pionter?[$isPointer], default[$defaultVal]\n" if $CDEBUG;
    }
    elsif ($line =~ $regexp->{structEnd}) {
        print "// found end of struct $structName\n" if $CDEBUG;
        if ($keyEndFlag) {
            print "// generated code\n" if $CDEBUG;
            generate($structName, $fieldList);
        }
        $structName = undef;
        $keyEndFlag = 0;
    }

    if (!$keyEndFlag) {
        # output origin line
        print "$line\n";
    }
}

# end main #

sub generate
{
    my ($structName, $fieldList) = @_;
    
    generate_ctor($structName, $fieldList);
    generate_detor($structName, $fieldList);
    generate_ReadIni($structName, $fieldList);
}

=pod
constructor sample:
    PSIni()
    {
        SectionA = nullptr;
        SectionB = nullptr;
        IniKey = 0;
        DoubleKey = 0.0;
        AnyKey = defaultVal;
    }
=cut
sub generate_ctor
{
    my ($structName, $fieldList) = @_;

    print "$indent$structName()\n";
    print "$indent\{\n";

    foreach my $field (@$fieldList) {
        my $type = $field->{type};
        my $name = $field->{name};
        my $isPointer = $field->{isPointer};
        my $defaultVal = $field->{defaultVal};
        if (isInt($type)) {
            $defaultVal ||= "0";
        }
        elsif (isDouble($type)) {
            $defaultVal ||= "0.0";
        }
        elsif ($isPointer) {
	    $defaultVal ||= "nullptr";
        }

	if (length($defaultVal) > 0) {
	    print "$indent$indent$name = $defaultVal;\n";
	}
    }
    
    print "$indent\}\n";
}

=pod
    ~PSIni()
    {
        delete SectionA;
        delete SectionB;
    }
=cut
sub generate_detor
{
    my ($structName, $fieldList) = @_;

    print "$indent~$structName()\n";
    print "$indent\{\n";

    foreach my $field (@$fieldList) {
        my $name = $field->{name};
        my $isPointer = $field->{isPointer};
        if ($isPointer) {
            print "${indent}${indent}delete $name;\n";
        }
    }
    
    print "$indent\}\n";
}

=pod
    template <typename mapType>
    void ReadIni(const mapType& iniMap)
    {
        READ_INI_KEY(SectionA, iniMap);
        READ_INI_KEY(SectionB, iniMap);
    }
=cut
sub generate_ReadIni
{
    my ($structName, $fieldList) = @_;

    print "${indent}template <typename mapType>\n";
    print "${indent}void ReadIni(const mapType& iniMap)\n";
    print "${indent}\{\n";

    foreach my $field (@$fieldList) {
        my $name = $field->{name};
        print "${indent}${indent}READ_INI_KEY($name, iniMap);\n";
    }

    print "$indent}\n";
}

sub isInt
{
    my ($type) = @_;
    if ($type =~ /int$/i) {
        return 1;
    }
    elsif ($type =~ /long$/i) {
        return 1;
    }
    return 0;
}

sub isDouble
{
    my ($type) = @_;
    if ($type =~ /double$/i) {
        return 1;
    }
    elsif ($type =~ /float$/i) {
        return 1;
    }
    return 0;
}
