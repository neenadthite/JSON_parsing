#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

#define CHAR_LENGTH 50 

int main()
{
	struct json_object *jsondata = { NULL };
	struct json_object *filedata = { NULL };
	struct json_ovject *usernamedata = { NULL };
	char UserName[CHAR_LENGTH];
	int filesize = NULL ;
	int filenobytes = NULL ;
	int *jsonstring = NULL ;

	jsondata = json_object_new_object();
	usernamedata = json_object_new_object();

	FILE *fptr = fopen("/home/user/data.json","r");
	if (NULL == fptr)
	{
			printf("file not open");
			return 0;
	}
	else
	{
			fseek(fptr, 0, SEEK_END);
			filesize = ftell(fptr);
			fseek(fptr, 0, SEEK_SET);

			jsonstring = malloc(filesize + 1);

			if(jsonstring != NULL)
			{
				filenobytes = fread(jsonstring, sizeof(int), filesize, fptr);
				if (NULL < filenobytes)
				{
					filedata = json_tokener_parse(jsonstring);			
							json_object_object_get_ex(filedata,"username",&usernamedata);
							printf("\n Extracted Username: %s",json_object_to_json_string(usernamedata));
							json_object_object_add(jsondata,"CustomerName",json_object_new_string(json_object_get_string(usernamedata)));
				}
				printf("\nString after adding username = %s",json_object_to_json_string(jsondata));
			}
	free(jsonstring);
	jsonstring = NULL;
	}
	fclose(fptr);
	return 0;
}