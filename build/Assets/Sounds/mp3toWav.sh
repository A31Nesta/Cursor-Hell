#! /bin/sh
for i in *.mp3
do
	sox "$i" "wav/$(basename -s .mp3 "$i").wav"
done