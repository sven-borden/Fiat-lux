#!/bin/bash

SOURCE_FOLDER="../source/"
RENDU_PATH="../source/rendu2.x"

cp "Makefile" $SOURCE_FOLDER
make -C $SOURCE_FOLDER clean
make -C $SOURCE_FOLDER depend
make -C $SOURCE_FOLDER
cp $RENDU_PATH "."

if [ -f "rendu2.x" ];
then

    i=1
    while [ $i -le 2 ]
    do
        echo "Running V0$i.txt!"
        "./"rendu2.x Verification "V0$i.txt" > "out_V0$i.txt"
        let "i++"
        echo "Done!"
    done


else
    echo "File rendu1.x does not exist."
fi



