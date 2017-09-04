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
        print OUT "\t\t\t// *INDENT-OFF*\n";
        my $else = "";
        foreach my $el (map {$_ eq "" ? () : $_} @vars) {
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
            } elsif ($el = /SerializableAttributeDictionary\<(\w+), (\w+)\> (\w+);/) {
                if ($1 eq 'QString') {
                    if (exists $typex{$2}) {
                        $el = "\t\t\t${else}__IF_HASH_FROM_JSON_TYPED(it, $3, $typex{$2})";
                    } elsif(exists $enums{$2}) {
                        $el = "\t\t\t${else}__IF_HASH_FROM_JSON_ENUM(it, $3, $2)";
                    } else {
                        $el = "\t\t\t${else}__IF_OBJHASH_FROM_JSON(it, $3, $2)";
                    }
                } elsif(exists $enums{$1}) {
                    if (exists $typex{$2}) {
                        $el = "\t\t\t${else}__IF_ENUM_LIST_FROM_JSON_TYPED(it, $3, $typex{$2})";
                    } elsif(exists $enums{$1}) {
                        $el = "\t\t\t${else}__IF_ENUM_LIST_FROM_JSON_ENUM(it, $3, $2)";
                    } else {
                        $el = "\t\t\t${else}__IF_ENUM_OBJLIST_FROM_JSON(it, $3, $2)";
                    }
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
        print OUT "\t\t\t// *INDENT-ON*\n";
        print OUT "\t\t}\n\t}\n";
        @vars = ();
    } else {
        print OUT "\n\t$class($jl)".(@_ ? "\n".join("\n", @_)."\n\t}\n" : " {}\n");
    }
    $created_constructor = 1;
}

my @sws; # skip whitespace
my @its; #iterators
sub parsefunc {
    my ($L, $arr) = @_;
    if (@its) {
        pop @its if $L =~ $its[$#its]->[1];
        $L =~ s/$_->[2]/$_->[0]/g foreach @its;
    }
    if (@sws) {
        for my $i (reverse(0..$#sws)) {
            my $re = $sws[$i];
            my $tabs = "\t" x $i;
            if ($L =~ s/^($tabs)$re/${1}${2}\/\/ ${3}/) {
                pop @sws;
            } else {
                $L =~ s/^\t//;
            }
        }
    }
    if ($L =~ /^\t+\{$/ && ($arr->[$#$arr] =~ s/^(\s*)(try|finally|checked|lock *\(\w+\))$/$1\/\/ $2 \{/)) {
        push @sws, qr/(${1})(\})$/;
        return undef;
    }
    if ($L =~ /^\s+return \w+;$/) { #replace some silly branches
        my $i = $#$arr;
        my $do_replace = 0;
        my $v;
        if ($arr->[$i] =~ /^\s+\}$/ && $i-- && $arr->[$i] =~ /^\s+(\w+) \= /) {
            $v = $1;
            if ($i-- && $arr->[$i] =~ /^\s+\{$/ && $i-- && $arr->[$i] =~ /^\s+else$/) {
                while ($i-- && $arr->[$i] =~ /^\s+\}$/ && $i-- && $arr->[$i] =~ /^\s+$v \= / &&
                        $i-- && $arr->[$i] =~ /^\s+\{$/ && $i-- && $arr->[$i] =~ /^\s+(else )?if/) {
                    if (not $1) {
                        $do_replace = 1;
                        last;
                    }
                }
            }
        }
        if ($do_replace) { # FIXME: bug in here
            my $j = $i;
            my $in_else;
            while ($i++ != $#$arr) {
                next if $arr->[$i] =~ /^\s+\{]$/;
                $arr->[++$j] = $arr->[$i];
                $arr->[$j] =~ s/^\s+\}$//;
                $arr->[$j] =~ s/^(\s+)else if\b/${1}if/;
                $arr->[$j] =~ s/^(\s+)$v \=/${1}return/;
                if ($in_else) {
                    $arr->[$j] =~ s/^\t//;
                } elsif ($arr->[$j] =~ s/^\s+else$//) {
                    $in_else = 1;
                }
            }
            pop @$arr while $#$arr != $j;
            return undef;
        }
    }
    return undef if $L =~ /^\s+finally \{\}$/;
    if (/while \((\w+)\.MoveNext\(\)\)/) {
        my $nm = $1;
        if ($arr->[$#$arr] =~ /(\w+\<\w+(?:, \w+)*\>)(?:\.\w+)* $nm \= ((?:\w+\.)*\w+)\.GetEnumerator\(\);/) {
            my ($c, $v) = ($1, $2);
            pop(@$arr);
            my $it = "it";
            $it .= scalar(@its)+1 if @its;
            $L =~ s/^(\s+)while \(\w+\.MoveNext\(\)\)/${1}for (${c}::iterator $it = ${v}.begin();\n$1\t\t$it != ${v}.end(); ++$it)/;
            push (@its, [$it, $1."}", qr/\b$v\.Current\b/]);
        }
    }
    return $L;
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

    my $in_get;
    my $in_set;
    my $mem_fun;

    while (<IN>) {
        s/[\n\r]+$//;
        if ($class) {
            next if /^$/;
            s/\b(this|base)\.//g;
            s/\bList\b/QList/g;
            s/\bDictionary\b/QHash/g;
            s/\bObservableDictionary\b/QMap/g;
            s/\bnull\b/NULL/g;
            s/\.Count\b/.count()/g;
            s/\buint\b/unsigned/g;
            s/\bSerializableAttributeDictionary\b/QHash/g;

            s/\.Contains\(/.contains\(/g;
            s/\.Append\(/.append(/g;
            s/\bstring\b/QString/g;
            s/([^!])QString\.IsNullOrWhiteSpace\((\w+)\)/$1$2.isNull() || $2\.contains(QRegExp("^\\\\s*\$"))/g;
            s/(!)QString\.IsNullOrWhiteSpace\((\w+)\)/$1($2.isNull() || $2\.contains(QRegExp("^\\\\s*\$")))/g;

            s/\bUtilityClass\.Clamp\(([^,]+), ?([^,]+), ?([^,)]+)\)/$1 < $2 ? $2 : ($1 > $3 ? $3 : $1)/g;
            if ($in_get) {
                die unless s/^\t\t//;
                if (/^\t\}$/) {
                    print OUT join("\n", @$in_get, $_)."\n";
                    $in_get = undef;
                } else {
                    $_ = parsefunc($_, $in_get);
                    push (@$in_get, $_) if defined $_;
                }
            } elsif ($in_set) {
                die unless s/^\t\t//;
                if (/^\t\}$/) {
                    print OUT join("\n", @$in_set, "\t}")."\n";
                    $in_set = undef;
                } else {
                    $_ = parsefunc($_, $in_set);
                    push (@$in_set, $_) if defined $_;
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
                } elsif (s/^\t\tget(;?)/\tconst $mem_fun->[0]->[0] $mem_fun->[0]->[1]() const$1/) {
                    if (s/;$/ {return $mem_fun->[0]->[1];}/) {
                        print OUT $_."\n";
                    } else {
                        $in_get = [$_];
                    }
                } elsif (s/^\t\tset(;?)/\tvoid $mem_fun->[0]->[1]($mem_fun->[0]->[0]\& v)$1/) {
                    if (s/;$/ {$mem_fun->[0]->[1] = v;}/) {
                        print OUT $_."\n";
                    } else {
                        $in_set = [$_];
                    }
                } else {
                    $_ = parsefunc($_, $mem_fun);
                    push (@$mem_fun, $_) if defined $_;
                }
            } elsif (/^\}/) { # namespace end occurs first, actually.
                print OUT "};\n" and next if $created_constructor;
                create_constructor();
            } elsif (s/^\t\t(private|public) (static)? ?(.*;)$/$3/) {
                #s/ _/ /;
                push @vars, $_;
                print OUT "\t".$_, "\n";
            } elsif (/^\t\t(private|public) (static|override)? ?((\w+ )*\w+(\(.*)?)$/) {
                $mem_fun = [[split(/ /, $3)]];
            }
        } elsif (/(?:public|internal)(?: abstract| sealed| static| partial)? (?:class|struct) (\w+)/ and not $C_H) {
            $class = $1;
            $C_H = uc $class."_H";
            print OUT "#ifndef $C_H\n#define $C_H\n".($jl ? "#include \"json_macros.h\"\n" : "")."\nclass $class {\npublic:\n";
        } elsif (/\t(?:public |internal )(?:class|struct) (\w+) : (\w+)/) {
            #die "feed abstract class first!" if not $C_H;
            $class = $1;
            $C_H = uc $class."_H";
            print OUT "\n\nclass $class : public $2 {\npublic:\n";

            #warn "unexpected inheritance: $2" if uc $2."_H" ne uc $C_H;
        } else {
            warn "Unhandled:$_\n";
        }
    }
    close IN;
}
print OUT "\n#endif // $C_H\n";
close OUT;
