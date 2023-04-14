#include <stdio.h>
#include <stdlib.h>
int recordSz;
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	int id;
	char name;
	int order;
	struct HashType* next;
};

// Compute the hash function
int hash(int x)
{
	int newOrder = x % 11;
	return newOrder;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	struct HashType *temp;
	for (i=0;i<hashSz;i++)
	{
		if(pHashArray[i].name == ' ')
		{
			continue;
		}
		printf("Index %d: ", i);
		for(temp = &pHashArray[i]; temp != NULL; temp = temp->next)
			{
				printf("Id: %d ", temp->id);
				printf("Name: %c ", temp->name);
				printf("Order: %d  ", temp->order);
			}
		printf("\n");
	}
	
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
	struct HashType *temp1, *temp2;
	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	int newOrder;
	struct HashType hashCode[11];
	for(int i = 0; i < 11; i++)
	{
		hashCode[i].id = 0;
		hashCode[i].name = ' ';
		hashCode[i].order = 0;
		hashCode[i].next = NULL;
	}
	//hashCode = (struct HashType*) malloc(sizeof(struct HashType) * recordSz);
	for(int i = 0; i < recordSz; i++)
	{
		int newOrder = hash(pRecords[i].id);
		temp1 = (struct HashType*) malloc(sizeof(struct HashType));
		temp1->id = pRecords[i].id;
		temp1->name = pRecords[i].name;
		temp1->order = pRecords[i].order;
		temp1->next = NULL;

		if(hashCode[newOrder].name == ' ')
		{
			hashCode[newOrder].id = temp1->id;
			hashCode[newOrder].name = temp1->name;
			hashCode[newOrder].order = temp1->order;
			hashCode[newOrder].next = temp1->next;
		}
		else
		{
			for(temp2 = &hashCode[newOrder]; temp2->next != NULL; temp2 = temp2->next)
			{
				//get to end of linked list
			}
			temp2->next = temp1;
		}
	}
	displayRecordsInHash(hashCode,11);
	free(temp1);
	free(pRecords);
}