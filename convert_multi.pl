#!/usr/bin/env perl
# (c) picobyte 2017

#usage: perl convert_multi.pl location.h ../hhs_/Location.cs

use warnings;
use strict;
use Scalar::Util qw/openhandle/;

my %enums = (map {$_ => ''} qw/OutfitType Payperiode Gender BodyPart Fetish FacialExpressions/);

my %typex = (unsigned => 'toInt', int => 'toInt', bool => 'toBool', double => 'toDouble', QString => 'toString');
my $typexr = join("|", keys %typex);
$typexr = qr/\b($typexr)\b/;

my $created_constructor;

my $class;
my @vars;
my $jl = "QJsonObject *d = NULL"; #json loadable
sub create_constructor {
    shift(@_) if @_;
    if (@vars && $jl) {
        shift(@_) if @_;
        print OUT "\n\t$class($jl)\n\t{\n\t\tif (d) init(d);\n".
        join("\n", @_)."\n\t}\n\tvoid init(QJsonObject *d)\n\t{\n";
        print OUT "\t\tfor (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {\n";
        my $else = "";
        foreach my $el (@vars) {
            if ($el =~ /(\w+) (\w+);/) {
                if (exists $typex{$1}) {
                    $el = "\t\t\t${else}__IF_VAR_FROM_JSON_AS(it, $2, $typex{$1})";
                } elsif(exists $enums{$1}) {
                    $el = "\t\t\t${else}__IF_ENUM_FROM_JSON_AS(it, $2, $1)";
                } else {
                    $el = "\t\t\t${else}__IF_OBJ_FROM_JSON_AS(it, $2)";
                }
            } elsif ($el =~ /QList\<(\w+)\> (\w+);/) {
                if (exists $typex{$1}) {
                    $el = "\t\t\t${else}__IF_LIST_FROM_JSON_TYPED(it, $2, $typex{$1})";
                } elsif(exists $enums{$1}) {
                    $el = "\t\t\t${else}__IF_LIST_FROM_JSON_ENUM(it, $2, $1)";
                } else {
                    $el = "\t\t\t${else}__IF_OBJLIST_FROM_JSON(it, $2, $1)";
                }
            } else {
                $el =~ s/^(.*);$/\t\t\t\/\/$1/;
                print OUT $el, "\n";
                next;
            }
            $el =~ s/\bBodyPart\b/Body::Part/g;
            $else = "else ";
            print OUT $el, "\n";
        }
        print OUT "\t\t}\n\t}\n";
        @vars = ();
    } else {
        print OUT "\n\t$class($jl)".(@_ ? "\n".join("\n", @_)."\n\t}\n" : " {}\n");
    }
    $created_constructor = 1;
}

my $C_H;
while (my $f = shift) {
    if (not -e $f) {
        if ($f =~ /-+nojso?n/i) {
            $jl = "";
        } else {
            open(OUT, ">$f") or die "$f$!";
        }
        next;
    }
    die unless openhandle(*OUT);
    open (IN, "<$f") or die "$f:$!";

    my $mem_fun;
    my $in_get;
    my $in_set;

    while (<IN>) {
        s/[\n\r]+$//;
        if ($class) {
            next if /^$/;
            s/\b(this|base)\.//g;
            s/\bList\b/QList/g;
            s/\bDictionary\b/QHash/g;
            s/\bObservableDictionary\b/QMap/g;
            s/\bnull\b/NULL/g;
            s/\buint\b/unsigned/g;
            s/\bstring\b/QString/g;
            s/\bUtilityClass\.Clamp\(([^,(]+), ?([^,]+), ?([^,)]+)\)/$1 < $2 ? $2 : ($1 > $3 ? $3 : $1)/g;
            if ($in_get) {
                die unless s/^\t\t//;
                if (/^\t\}$/) {
                    print OUT join("\n", @$in_get, $_)."\n";
                    $in_get = undef;
                } else {
                    push @$in_get, $_;
                }
            } elsif ($in_set) {
                die unless s/^\t\t//;
                if (/^\t\}$/) {
                    print OUT join("\n", @$in_set, "\t}")."\n";
                    $in_set = undef;
                } else {
                    push @$in_set, $_;
                }
            } elsif ($mem_fun) {
                die unless s/^\t//;
                if (/^\t\}$/) {
                    $mem_fun->[0] = "\t".join(" ", @{$mem_fun->[0]});
                    if ($mem_fun->[0] =~ /^\t$class\(/) {
                        create_constructor(@$mem_fun);
                    } elsif (@$mem_fun > 2) {
                        print OUT join("\n", @$mem_fun, $_)."\n";
                    }
                    $mem_fun = undef;
                } elsif ($mem_fun->[0]->[0] =~ /^\t$class\(/) { # constructor
                    push (@$mem_fun, $_) unless / \= new \w+\<\w+\>\(\);/;
                } elsif (s/^\t\tget(;?)/\tconst $mem_fun->[0]->[0] get_$mem_fun->[0]->[1]() const$1/) {
                    if (s/;$/ {return $mem_fun->[0]->[1];}/) {
                        print OUT $_."\n";
                    } else {
                        $in_get = [$_];
                    }
                } elsif (s/^\t\tset(;?)/\tvoid set_$mem_fun->[0]->[1]($mem_fun->[0]->[0]\& v)$1/) {
                    if (s/;$/ {$mem_fun->[0]->[1] = v;}/) {
                        print OUT $_."\n";
                    } else {
                        $in_set = [$_];
                    }
                } else {
                    push @$mem_fun, $_;
                }
            } elsif (/^\}/) { # namespace end occurs first, actually.
                print OUT "};\n" and next if $created_constructor;
                create_constructor();
            } elsif (s/^\t\t(private|public) (static)? ?(.*;)$/$3/) {
                s/ _/ /;
                push @vars, $_;
                print OUT "\t".$_, "\n";
            } elsif (/^\t\t(private|public) (static|override)? ?((\w+ )*\w+(\(.*)?)$/) {
                $mem_fun = [[split(/ /, $3)]];
            }
        } elsif (/public(?: abstract)? class (\w+)/ and not $C_H) {
            $class = $1;
            $C_H = uc $class."_H";
            print OUT "#ifndef $C_H\n#define $C_H\n".($jl ? "#include \"json_macros.h\"\n" : "")."\nclass $class {\npublic:\n";
        } elsif (/\tpublic class (\w+) : (\w+)/) {
            die "feed abstract class first!" if not $C_H;
            $class = $1;
            print OUT "\n\nclass $class : public $2 {\npublic:\n";

            warn "unexpected inheritance: $2" if uc $2."_H" ne uc $C_H;
        } else {
            warn "Unhandled:$_\n";
        }
    }
    close IN;
}
print OUT "\n#endif // $C_H\n";
close OUT;
