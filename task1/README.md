# task 1
In this project you can count words in text and find information about them in opencorpa dict

1. put texts files in directory ./texts
2. put [opencorpora](http://opencorpora.org/files/export/dict/dict.opcorpora.xml.zip) xml dictionary in ./dict directory
3. build project in any convenient way
4. run

##### Possible output:
```asm
и: total count is 16076
        id: 178876, не: PRCL

с: total count is 3659
Possible lemmas id are: 311151 389603 389604 390197 390198 390349
        id: 311151, с: PREP
        id: 389603, с: NOUN inan femn Fixd Abbr
        id: 389604, с: NOUN inan neut Fixd Abbr
        id: 390197, с: NOUN anim ms-f Sgtm Fixd Abbr Name Init
        id: 390198, с: NOUN anim ms-f Sgtm Fixd Abbr Patr Init
        id: 390349, с: PRCL

он: total count is 3366
Possible lemmas id are: 206541
        id: 206541, он: NPRO masc 3per Anph

его: total count is 3034
Possible lemmas id are: 94208 206541 206649
        id: 94208, его: ADJF Fixd Apro Anph
        id: 206541, он: NPRO masc 3per Anph
        id: 206649, оно: NPRO neut 3per Anph
```
