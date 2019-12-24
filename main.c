#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define begin 9//начало работы
#define end 21//конец работы

typedef struct {
	char name[40];//название 
	int time;//время
}hairstyle;//описание прически

typedef struct {
	int min;
	int pr;
}time;//структура описания времени

typedef struct {
	char name[50];
	hairstyle rec;
	int time[2];
}client;

int time_work = (end - begin) * 60;//время работы в минутах
client man[30];//массив клиентов за день
int counter = 0;//счетчик записей за день
hairstyle list[10] = { { "hair1", 30 },//массив причесок "название, время исполнения"
							{ "hair2", 40 },
							{ "hair3", 50 },
							{ "hair4", 60 },
							{ "hair5", 65 },
							{ "hair6", 45 },
							{ "hair7", 82 },
							{ "hair8", 23 },
							{ "hair9", 54 },
							{ "hair10", 23 } };


void record(time[]);//запись в парикмахерскую
void delet(time[]);//удаление записи из списка
void out_record();//вывод на экран списка записей

int main()
{
	//setlocale(LC_ALL, "rus");//для корректной работы кириллицы
	int a = 0;//переменная для switch
	time Time[(end - begin) * 60];//массив времени работы в минутах
	int i = 0;//для циклов
	for (i = 0; i < time_work; i++)//инициализация времени работы парикмахерской
	{
		Time[i].min = i;//номер минуты
		Time[i].pr = 0;//показатель "свободно/занято"
	}
	do {//стандартный выбор через switch
		system("cls");
		printf("Выберите действие\n\n");
		printf("1.Записаться на стрижку\n2.Вывести записи\n3.Удаление из списка\n4.Выход\n");
		scanf("%i", &a);
		switch (a)
		{
		case 1:
			record(Time);
			break;
		case 2:
			out_record();
			system("pause");
			break;
		case 3:
			if (counter)//если записец нет, то удалять нечего
				delet(Time);//и функция удаления не вызывается
			else
				printf("\nЗаписей нет!");
			break;
		case 4:
			break;
		default: printf("Введите 1-4");
		}
	} while (a != 4);
	system("pause");
	return 0;
}

void Print()//вывод списка причесок для выбора
{
	int i;
	printf("Прическа\t\tвремя выполнения");
	for (i = 0; i < 10; i++)
	{
		printf("\n%i.%s\t\t%i:%i", i + 1, list[i].name, list[i].time / 60, list[i].time % 60);
	}
}

void delet(time T[])
{
	client r;//впомогательная переменная
	int n, i;
	system("cls");
	out_record();//вывод списка записей
	do {
		printf("\nВведите порядковый номер записи для удаления: ");
		scanf("%i", &n);//ввод номера удаляемой записи
		if (n < 1 || counter < n)
			printf("Введите номер из списка!\n");
	} while (n < 1 || counter < n);
	n--;
	for (i = 60 * (man[n].time[0] - begin) + man[n].time[1]; i < 60 * (man[n].time[0] - begin) + man[n].time[1] + man[n].rec.time; i++)
	{
		/*освобождаем минуты с "времени записи на стрижку" до "время записи на стрижку + время самой стрижки"*/
		T[i].pr = 0;//при удалении записи "освобождаем" время, которое было "занято" в массиве работы парикмахерской
		//printf("\n%i %i", T[i].min, T[i].pr);
	}

	if (n != counter - 1)//если удаляемая запись не последняя
	{
		r = man[n];//то меняем ее с последней записью 
		man[n] = man[counter - 1];
		man[counter - 1] = r;
	}
	system("pause");
	counter--;//уменьшаем счетчик
}

void sort()
{//сортировка пузырьком по времени записи
	client r;
	int i, j;
	if (counter < 2)
		return;
	for (i = 0; i < counter - 1; i++)
		for (j = i + 1; j < counter; j++)
			if (man[i].time[0] > man[j].time[0])
			{
				r = man[i];
				man[i] = man[j];
				man[j] = r;
			}
}

void out_record()
{//вывод записей на экран
	int i;
	printf("\nЗаписи\n\n");
	sort();
	for (i = 0; i < counter; i++)
	{
		printf("\n%i.%s", i + 1, man[i].name);//вывод имени
		printf("%i:", man[i].time[0]);//вывод часа
		if (man[i].time[1] < 10)//если минуты равны 0-9
			printf("0");//то приписываем 0 впереди чтоб получилось "9 00", а не "9 0"
		printf("%i - ", man[i].time[1]);//вывод минут
		printf("%i:", ((60 * man[i].time[0]) + man[i].time[1] + man[i].rec.time) / 60);
		if ((man[i].time[1] + man[i].rec.time) % 60 < 10)//вывод времени до которого длится стрижка
			printf("0");
		printf("%i", (man[i].time[1] + man[i].rec.time) % 60);
	}
	printf("\n");
}

void record(time T[])
{
	system("cls");
	int i, j;
	int time_rec[2];//времени
	int n;
	fflush(stdin);
	printf("Введите имя и фамилию: ");
	getchar();
	fgets(man[counter].name, 50, stdin);
	if (counter)
	{
		out_record();//вывод записей, если они есть
	}
	do {
		printf("\nВведите время, на которое хотите записаться(например 11 00): ");
		scanf("%i%i", &time_rec[0], &time_rec[1]);//ввод времени на которое хочет записаться пользователь
		if (time_rec[0] < begin || end <= time_rec[0])//если время выходит за рамки режима работы, то просим ввести время заново
			printf("\nВведите время в пределах %i - %i\n\n", begin, end);
	} while (time_rec[0] < begin || end <= time_rec[0]);//если время выходит за рамки режима работы, то запускаем ввод заново
	man[counter].time[0] = time_rec[0];//запись времени в массив записей(часов)
	man[counter].time[1] = time_rec[1];//запись времени в массив записей(минут)
	Print();//вывод списка стрижек, для выбора
	printf("\nВыберите прическу (введите порядковый номер): ");
	scanf("%i", &n);//считывание номера стрижки
	n--;
	man[counter].rec = list[n];//копирование данных о стрижке
	for (i = 0; i < time_work; i++)
	{
		if (time_rec[0] == (T[i].min / 60) + begin && time_rec[1] == (T[i].min % 60))/*поиск минуты в массиве
																					 соответсвующей введенному времени*/
			if (T[i].min + list[n].time <= T[time_work - 1].min)//если стрижка не укладывается в режим работы, то не записываем
			{
				int flag = 0;
				for (j = i; j < T[i].min + list[n].time; j++)
				{
					if (T[j].pr == 1) flag = 1;
				}
				if (flag == 0)
				{
					for (j = i; j < T[i].min + list[n].time; j++)
					{
						T[j].pr = 1;
					}
					counter++;
				}
				else
				{
					printf("Вы не можете записаться на данное время!!!\n\n");
					system("pause");
					break;
				}
				system("pause");
				break;
			}
	}
}
