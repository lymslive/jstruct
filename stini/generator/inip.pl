#! /usr/bin/env perl
# convert .ini config to .properties config
package inip;
use strict;
use warnings;

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
#my $secList = [];
#my $prevsec = undef;
my $section = undef;
my $iniKey = undef;
my $iniVal = undef;

## main loop
while (<>) {
    chomp;
    my $line = $_;
    if ($line =~ $regexp->{emptyLine}) {
	print "\n";
    }
    elsif ($line =~ $regexp->{commentLine}) {
	$line =~ s/^\s*;/#/;
	print "$line\n";
    }
    elsif ($line =~ $regexp->{section}) {
	$section = $1;
	print "#$line\n";
    }
    elsif ($line =~ $regexp->{keyvalue}) {
	$iniKey = $1;
	$iniVal = $2;
	print "$section.$iniKey = $iniVal\n";
    }
}
