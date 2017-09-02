#!/usr/bin/env perl
# (c) picobyte 2017

use warnings;
use strict;
use Scalar::Util qw/openhandle/;

my $C_H;
while (my $f = shift) {
    if (not -e $f) {
        open(OUT, ">$f") or die "$f$!";
        next;
    }
    die unless openhandle(*OUT);
    open (IN, "<$f") or die "$f:$!";
    my $class;

    my @vars;
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
            s/\bstring\b/QString/g;
            if ($in_get) {
                if (s/^\t\t\t\}$//) {
                    print OUT join("\n", @$in_get, "\t}")."\n";
                    $in_get = undef;
                } else {
                    s/^\t\t//;
                    push @$in_get, $_;
                }
            } elsif ($in_set) {
                if (s/^\t\t\t\}$//) {
                    print OUT join("\n", @$in_set, "\t}")."\n";
                    $in_set = undef;
                } else {
                    s/^\t\t//;
                    push @$in_set, $_;
                }
            } elsif ($mem_fun) {
                if (s/^\t\t\}$//) {
                    if (@$mem_fun > 2) {
                        $mem_fun->[0] = join(" ", @$mem_fun[0]);
                        print OUT join("\n", @$mem_fun, "\t}")."\n";
                    }
                    $mem_fun = undef;
                } elsif (s/^\t\t\tget(;?)$/\tconst $mem_fun->[0]->[0] get_$mem_fun->[0]->[1]() const$1/) {
                    if (s/;$/ {return $mem_fun->[0]->[1];}/) {
                        print OUT $_."\n";
                    } else {
                        $in_get = [$_];
                    }
                } elsif (s/^\t\t\tset(;?)$/\tvoid set_$mem_fun->[0]->[1]($mem_fun->[0]->[0]\& v)$1/) {
                    if (s/;$/ {$mem_fun->[0]->[1] = v;}/) {
                        print OUT $_."\n";
                    } else {
                        $in_set = [$_];
                    }
                } else {
                    s/^\t//;
                    push @$mem_fun, $_;
                }
            } elsif (/^\t\}/) {
                #create constructor;
                if (@vars) {
                    print OUT "\n\t$class(QJsonObject *d = NULL)\n\t{\n\t\tif (d) init(d);\n\t}\n\tvoid init(QJsonObject *d)\n\t{\n";
                    print OUT "\t\tfor (QJsonObject::iterator it = d->begin(); it != d->end(); ++it) {\n";
                    my $else = "";
                    foreach my $el (@vars) {
                        if ($el =~ /(?:int|bool|double|QString)/) {
                            $el =~ s/^(?|(i)(nt)|(b)(ool)|(d)(ouble)|Q(S)(tring)) (\w+);$/\t\t\t${else}__IF_VAR_FROM_JSON_AS(it, $3, to\U$1\L$2)/;
                            $else = "else ";
                        } else {
                            $el =~ s/^(.*);$/\t\t\t\/\/$1/;
                        }
                        #$el =~ s/(Array|Object|Variant) (\w+);$/$2(v["$2"].to${1:+\U:\L}())/;
                        print OUT $el, "\n";
                    }
                    print OUT "\t\t}\n\t}\n};";
                    @vars = ();
                } else {
                    print OUT "\n\t$class(QJsonObject *d = NULL) {}\n};";
                }
            } elsif (s/^\t\t(private|public) (static)?(.*;)$/$3/) {
                s/ _/ /;
                push @vars, $_;
                print OUT "\t".$_, "\n";
            } elsif (/^\t\t(private|public) (static|override)?(\w+) (\w+)$/) {
                $mem_fun = [[$3, $4]];
            }
        } elsif (/public(?: abstract)? class (\w+)/ and not $C_H) {
            $class = $1;
            $C_H = uc $class."_H";
            print OUT "#ifndef $C_H\n#define $C_H\n#include \"json_macros.h\"\n\nclass $class {\npublic:\n";
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
print OUT "\n\n#endif // $C_H\n";
close OUT;
