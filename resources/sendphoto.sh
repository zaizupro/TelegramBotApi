#!/bin/sh

TOKEN=${1}
CHATID=${2}
FILENAME=${3}

curl -s -X POST "https://api.telegram.org/bot${TOKEN}/sendPhoto" -F chat_id=${CHATID} -F photo="@${FILENAME}"
