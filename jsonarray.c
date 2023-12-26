#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

#define CHAR_LENGTH 50 

int main(){
    struct json_object *parsed_array = { NULL };
    struct json_object *arraydata = { NULL };
    struct json_object *jsondata = { NULL };
	struct json_object *firstname = { NULL };
	struct json_object *customerid = { NULL };

    int filesize = NULL ;
	int filenobytes = NULL ;
	int *jsonstring = NULL ;
	char strfirstname[CHAR_LENGTH];
	char strcustomerid[CHAR_LENGTH];

	parsed_array = json_object_new_object();
	arraydata = json_object_new_object();
	firstname = json_object_new_object();
	customerid = json_object_new_object();

	FILE *fptr = fopen("/home/root/customerdata.json","r");
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
                    parsed_array = json_tokener_parse(filenobytes);
                    json_object_object_get_ex(parsed_array,"records",&arraydata);
					int arraylength = json_object_array_length(arraydata);
					for(int i=0; i<arraylength; i++)
					{
						jsondata = json_object_array_get_idx(arraydata, i);
						printf("%s",json_object_to_json_string(jsondata));	
						if (json_object_object_get_ex(jsondata, "FirstName", &firstname))
						{
							strcpy(strfirstname,json_object_new_string(json_object_to_json_string(firstname)));
							printf("%s",strfirstname);
						}
						if (json_object_object_get_ex(jsondata, "CustomerID", &customerid))
						{
							strcpy(strfirstname,json_object_new_string(json_object_to_json_string(customerid)));
							printf("%s",strcustomerid);
						}
					}
	            }
			}
	free(jsonstring);
	jsonstring = NULL;
	}
	fclose(fptr);
return 0;
}