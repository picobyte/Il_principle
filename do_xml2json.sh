#!/bin/bash
# convert all xml files in Schools to . json files

find Schools/ -type f -name "*.xml" |
parallel -n 1 -j 8 python2.7 xml2json/xml2json.py --pretty --strip_text -o {.}.json {} | tee -a xml2json.err


