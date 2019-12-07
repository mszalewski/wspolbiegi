#!/bin/bash

digit='^[0-9]+$'


user_path=$(echo $HOME)
user=$(whoami)
klient="/home/$user/Szkola/wspolbiezne/lab04/klientfifo"
serwer="/home/$2/Szkola/wspolbiezne/lab04/serwerfifo"


if [[ ! -p $serwer ]]; then
  echo "nie mozna sie polaczyc z laczem serwera $serwer"
  exit 1
fi


if [[ "$1" ]]; then
  echo $user $1 >$serwer
  if [[ -p $klient ]]; then
    while true
    do
      if read line <$klient; then
          echo $line
          if [[ "$line" =~ $digit ]]; then
            exit 0
          else
            exit 0
          fi
      fi
    done
      else
        echo "nie ma lacza klienta"
  fi
else
  echo "podaj prawidlowy argument polecenia"
fi