#include <stdio.h>
#include "mysql.h"
#include <string.h>
#pragma comment(lib, "libmysql.lib")
#define MAXCHAR 10000

const char* host = "localhost";
const char* user = "root";
const char* pw = "mysql";
const char* db = "project";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	FILE* file;
	char str[MAXCHAR];
	bool exit = false;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");

		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		//create_table 파일 읽어오기
		if ((file = fopen("create_table.txt", "r")) == NULL) {
			printf("error : create_table open\n");
			mysql_close(connection);
			return 1;
		}
		while (fgets(str, MAXCHAR - 1, file) != NULL) {
			const char* query = str;
			int state = 0;
			state = mysql_query(connection, query);
		}
		fclose(file);

		//insert_table 파일 읽어오기
		if ((file = fopen("insert_table.txt", "r")) == NULL) {
			printf("error : insert_table open\n");
			mysql_close(connection);
			return 1;
		}
		while (fgets(str, MAXCHAR - 1, file) != NULL) {
			const char* query = str;
			int state = 0;
			state = mysql_query(connection, query);
		}
		fclose(file);


		while (!exit) {
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE I\n");
			printf("\t2. TYPE II\n");
			printf("\t3. TYPE III\n");
			printf("\t4. TYPE IV\n");
			printf("\t5. TYPE V\n");
			printf("\t0. QUIT\n");
		
			int n;
			int year;
			int month;
			scanf("%d", &n);
			switch (n) {
			case 1:{
				int truck_num;
				printf("Which Truck Number? : ");
				scanf("%d", &truck_num);
				if (truck_num == 0) {
					break;
				}
				while (1) {
					int sub_n;
					char st[1000];
					printf("----- Subtypes in TYPE I -----\n");
					printf("\t1. TYPE I-1.\n");
					printf("\t2. TYPE I-2.\n");
					printf("\t3. TYPE I-3.\n");
					printf("\t0. Exit.\n");
					scanf("%d", &sub_n);
					if (sub_n == 0) {
						break;
					}
					else if (sub_n == 1) {
						printf("---- TYPE I-1 ----\n\n");
						printf("**Find all customers who had a package on the truck at the time of the crash.**\n");
						sprintf(st, "SELECT C.Name FROM Customer C INNER JOIN Shipment S ON C.Customer_ID = S.Customer_ID INNER JOIN Location L ON S.Shipment_ID = L.Shipment_ID WHERE L.Position_Type = 'truck' AND L.Name_ID = '%d' AND L.State = 'crash'", truck_num);
						const char* query = st;
						int cnt = 0;
						int state = 0;
						state = mysql_query(connection, query);
						if (state == 0)
						{
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("%s\n", sql_row[0]);
								cnt++;
							}
							if (cnt == 0) {
								printf("truck %d didn't crush\n", truck_num);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("%s\n", mysql_error(connection));
						}

					}
					else if (sub_n == 2) {
						printf("---- TYPE I-2 ----\n\n");
						printf("**Find all recipients who had a package on that truck at the time of the crash.**\n");
						sprintf(st, "SELECT R.Name FROM Recipient R INNER JOIN Shipment S ON R.Recipient_ID = S.Recipient_ID INNER JOIN Location L ON S.Shipment_ID = L.Shipment_ID WHERE L.Position_Type = 'truck' AND L.Name_ID = '%d' AND L.State = 'crash'", truck_num);
						const char* query = st;
						int state = 0;
						state = mysql_query(connection, query);
						int cnt = 0;
						if (state == 0)
						{
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("%s\n", sql_row[0]);
								cnt++;
							}
							if (cnt == 0) {
								printf("truck %d didn't crush\n", truck_num);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("%s\n", mysql_error(connection));
						}
					}
					else if (sub_n == 3) {
						printf("---- TYPE I-3 ----\n\n");
						printf("**Find the last successful delivery by that truck prior to the crash.**\n");
						sprintf(st, "SELECT S.Items FROM Shipment S INNER JOIN Location L ON S.Shipment_ID = L.Shipment_ID WHERE L.Position_Type = 'truck' AND L.Name_ID = '%d' AND L.State = 'arrive' AND L.End_Time = ( SELECT MAX(End_Time) FROM Location WHERE Position_Type = 'truck' AND Name_ID = '%d' AND State = 'arrive' AND End_Time < ( SELECT MAX(End_Time) FROM Location WHERE Position_Type = 'truck' AND Name_ID = '%d' AND State = 'crash' ) )", truck_num, truck_num, truck_num);
						const char* query = st;
						int state = 0;
						state = mysql_query(connection, query);
						int cnt = 0;
						if (state == 0)
						{
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
							{
								printf("%s\n", sql_row[0]);
								cnt++;
							}
							if (cnt == 0) {
								printf("truck %d didn't crush\n", truck_num);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("%s\n", mysql_error(connection));
						}
					}
					else {
						printf("Please pick a number from 1 to 3 or 0\n");
					}

				}

				break;
			}
			case 2: {
				printf("---- TYPE II ----\n\n");
				printf("**Find the customer who has shipped the most packages in the past year.**\n");
				printf("Which Year? : ");
				scanf("%d", &year);
				char st[1000];
				sprintf(st, "SELECT C.Name, COUNT(S.Shipment_ID) AS Shipment_Count FROM Customer C JOIN Shipment S ON C.Customer_ID = S.Customer_ID WHERE YEAR(S.Order_Time) = %d GROUP BY C.Name HAVING COUNT(S.Shipment_ID) = ( SELECT MAX(Shipment_Count) FROM( SELECT COUNT(Shipment_ID) AS Shipment_Count FROM Shipment WHERE YEAR(Order_Time) = % d GROUP BY Customer_ID ) AS T )", year, year);
				const char* query = st;
				int state = 0;
				state = mysql_query(connection, query);

				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s %s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("%s\n", mysql_error(connection));
				}
				break;
			}
			case 3: {
				printf("---- TYPE III ----\n\n");
				printf("**Find the customer who has spent the most money on shipping in the past year.**\n");
				printf("Which Year? : ");
				scanf("%d", &year);
				char st[1000];
				sprintf(st, "SELECT C.Name FROM Customer C JOIN Bill_Cus BC ON C.Customer_ID = BC.Customer_ID JOIN Bill B ON BC.Bill_ID = B.Bill_ID WHERE YEAR(B.Billing_Date) = %d GROUP BY C.Customer_ID, C.Name HAVING SUM(B.Price) = ( SELECT MAX(Total_Price) FROM( SELECT SUM(B2.Price) AS Total_Price FROM Bill_Cus BC2 JOIN Bill B2 ON BC2.Bill_ID = B2.Bill_ID WHERE YEAR(B2.Billing_Date) = %d GROUP BY BC2.Customer_ID ) AS T ) ", year, year);
				const char* query = st;
				int state = 0;
				state = mysql_query(connection, query);

				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("%s\n", mysql_error(connection));
				}
				break;
			}
			case 4: {
				printf("---- TYPE IV ----\n\n");
				printf("**Find the packages that were not delivered within the promised time.**\n");
				const char* query = "SELECT S.Shipment_ID, S.Items FROM Shipment S JOIN Ship_Ser SS ON S.Shipment_ID = SS.Shipment_ID WHERE TIMESTAMPDIFF(HOUR, S.Order_Time, S.Receive_Time) > CASE WHEN SS.Timeliness = 'overnight' THEN 24 WHEN SS.Timeliness = 'second day' THEN 48 WHEN SS.Timeliness = 'longer' THEN 720 END OR S.Receive_Time IS NULL";
				int state = 0;
				state = mysql_query(connection, query);

				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s %s\n", sql_row[0], sql_row[1]);
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("%s\n", mysql_error(connection));
				}
				break;
			}
			case 5: {
				printf("---- TYPE V ----\n\n");
				printf("**Generate the bill for each customer for the past month.**\n");
				printf("Which Year? : ");
				scanf("%d", &year);
				printf("Which Month? : ");
				scanf("%d", &month);

				char st[1000];
				sprintf(st, "SELECT C.Name, C.Address, SUM(CASE WHEN B.State = 0 THEN B.Price ELSE 0 END) AS Outstanding_Amount FROM Customer C LEFT JOIN Bill_Cus BC ON C.Customer_ID = BC.Customer_ID LEFT JOIN Bill B ON BC.Bill_ID = B.Bill_ID WHERE YEAR(B.Billing_Date) = %d AND MONTH(B.Billing_Date) = %d GROUP BY C.Customer_ID ", year, month);
				const char* query = st;
				int state = 0;
				state = mysql_query(connection, query);

				printf("--------------------------- Simple Bill ---------------------------\n");
				printf("--------------Name-----------Address-------------Price--------------\n");

				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%18s%18s%18s\n", sql_row[0], sql_row[1], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("%s\n", mysql_error(connection));
				}

				printf("---------------------------------------------------------------------\n");



				break;
			}
			case 0:
				exit = true;
				break;
			default:
				printf("Please pick a number from 1 to 5 or 0\n");
				break;
			}
		
		}

		//drop_table 파일 읽어오기
		if ((file = fopen("drop_table.txt", "r")) == NULL) {
			printf("error : drop_table open\n");
			mysql_close(connection);
			return 1;
		}
		while (fgets(str, MAXCHAR - 1, file) != NULL) {
			const char* query = str;
			int state = 0;

			state = mysql_query(connection, query);
		}
		fclose(file);
		mysql_close(connection);
	}

	return 0;
}

/*
const char* query = "select * from student";
		int state = 0;

		state = mysql_query(connection, query);
		if (state == 0)
		{
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("%s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
			}
			mysql_free_result(sql_result);
		}
*/



/*

	printf("------- SELECT QUERY TYPES -------\n\n");
	printf("\t1. TYPE 1\n");
	printf("\t2. TYPE 2\n");
	printf("\t3. TYPE 3\n");
	printf("\t4. TYPE 4\n");
	printf("\t5. TYPE 5\n");
	printf("\t6. TYPE 6\n");
	printf("\t7. TYPE 7\n");
	printf("\t0. QUIT\n");
	//printf("----------------------------------\n");
	printf("\n\n");
	printf("---- TYPE 5 ----\n\n");
	printf("** Find the top k brands by unit sales by the year**\n");
	printf(" Which K? : 3\n");

	return 0;

}
*/