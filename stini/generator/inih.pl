#! /usr/bin/env perl
package inih;
use strict;
use warnings;

## const config, can read from environment variables INIH_*
my $CDEBUG     = $ENV{INIH_CDEBUG}     // 0;
my $LIBSTINI   = $ENV{INIH_LIBSTINI}   // "stini.hpp";
my $OHPPFILE   = $ENV{INIH_OHPPFILE}   // "config.ini.hpp";
my $INDENT     = $ENV{INIH_INDENT}     // '    '; # 4 space
my $ENDMACRO   = $ENV{INIH_ENDMACRO}   // 'END_INI_KEY';
my $STRTYPE    = $ENV{INIH_STRTYPE}    // 'std::string';
my $INIROOT    = $ENV{INIH_INIROOT}    // 'StIni'; # the root ini struct type name
my $SECPREFIX  = $ENV{INIH_SECPREFIX}  // 'Se';  # the section struct type name prefix
my $SECPOINTER = $ENV{INIH_SECPOINTER} // 0;

## regexp config
my $regexp = {
    section     => '^\s*\[(\w+)\]',
    keyvalue    => '^\s*(\w+)\s*=\s*(\S+)',
    intVlaue    => '^[-+0-9]+$',
    doubleVlaue => '^[-+0-9.eE]+$',
    emptyLine   => '^\s*$',
    commentLine => '^\s*[#;]',
};

## global variables
my $secList = [];
my $prevsec = undef;
my $section = undef;
my $iniKey = undef;
my $iniVal = undef;

## main loop
while (<>) {
    chomp;
    my $line = $_;
    if ($line =~ $regexp->{emptyLine} || $line =~ $regexp->{commentLine}) {
        next;
    }
    elsif ($line =~ $regexp->{section}) {
        $section = $1;
        onBeginSection($section, $prevsec);
        $prevsec = $section;
        push(@$secList, $section);
    }
    elsif ($line =~ $regexp->{keyvalue}) {
        $iniKey = $1;
        $iniVal = $2;
        onIniKey($iniKey, $iniVal);
    }
}
if (@$secList) {
    onIniEnd($secList);
}

## End Main ##

# begin a new [section], may need to end the last section
sub onBeginSection
{
    my ($section, $prevsec) = @_;
    
    if (!$prevsec) {
        onIniBegin();
    }
    elsif ($section ne $prevsec) {
        endPrevSection();
    }
    print "struct ${SECPREFIX}${section}\n";
    print "\{\n";
}

sub endPrevSection
{
    print "\n";
    print "${INDENT}${ENDMACRO};\n";
    print "\};\n";
    print "\n";
}

# when define a ini itme: key = val
sub onIniKey
{
    my ($key, $val) = @_;
    my $name = $key;
    my $type = $STRTYPE;

    if ($val =~ $regexp->{intVlaue}) {
        $type = "int";
    }
    elsif ($val =~ $regexp->{doubleVlaue}) {
        $type = "double";
    }
    else {
        $val = qq{"$val"}; # quote string val in cpp
    }

    print "${INDENT}${type} ${name} = ${val};\n";
}

# begin of the whole ini file
=pod
    #ifndef CONFIG_INI_HPP__
    #define CONFIG_INI_HPP__

    #include "stini.hpp"
=cut
sub onIniBegin
{
    my $hppfile = $OHPPFILE;
    $hppfile =~ s/(\S+)/\U$1/g; # to upper case
    $hppfile =~ s/\./_/g;
    $hppfile .= '__';

    print "#ifndef ${hppfile}\n";
    print "#define ${hppfile}\n";
    print "\n";
    print "#include \"${LIBSTINI}\"\n";
    print "\n";
}

# end of the whole ini file
sub onIniEnd
{
    my ($secList) = @_;

    endPrevSection();

    print "struct ${INIROOT}\n";
    print "\{\n";
    foreach my $section (@$secList) {
        if (${SECPOINTER}) {
            print "${INDENT}${SECPREFIX}${section}* ${section};\n"
        }
        else
        {
            print "${INDENT}${SECPREFIX}${section} ${section};\n"
        }
    }
    # print "\}\n";
    endPrevSection();
    print "#endif\n";
}
