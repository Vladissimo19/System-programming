#!/bin/bash
echo "Скрипт проверки файлов"
echo "Данный скрипт показывает, где Вы находитесь.Проверяет на существование введенные файлы.Определяет, изменялся ли файл после конкретной даты"
echo "Скрипт разработан Лешковым Владиславом Ярославовичем, гр. 736-1"
echo "Имя текущего каталога: $( pwd | tr / "\n" | tail -1 )"
echo "Файлы находящиеся в данном каталоге : $( ls )"
while :
	do
	read -p "Введите имя файла: " filename
	while :
		do
		if [ ! -f "$filename" ]
			then
				echo "Файл $filename не существует" 1>&2
				read -p "Вы желаете начать выполнение занова? (yes/no) ." check
				if [ "$check" = "no" ];
				then
					exit 0
				elif [ "$check" = "yes" ];
				then 
					read -p "Введите имя файла повторно: " filename
				else
					echo " Неверный ввод, выход из программы " 1>&2
					exit 0
				fi

		else
			echo "Файл $filename найден!"
			break
		fi
	done
	read -p "Введите дату для проверки на изменения файла (Формат ввода: Tue Feb 25 2020) " checkdate
	if [ "$(date -r "$filename" +%s)" -gt "$(date --date="$checkdate" +%s)" ] ;
	then
		echo "Файл $filename был изменен после $checkdate "
		exit 120
	else
		echo "Файл $filename не был изменен после $checkdate " 
	fi
	while :
		do
			read -p "Вы желаете начать выполнение занова? (yes/no). " check
			if [ "$check" = "no" ];
			then
				exit 0
			elif [ "$check" = "yes" ];
			then	
				break
			else 
				echo "Неверный ввод, выход из программы" 1>&2
				exit 0					
		fi
	done	
done
