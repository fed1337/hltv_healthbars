#include "stdafx.h"

struct tag_s
{
	tag_s* pNext;
	char* szTag;
};

tag_s* head = NULL;

// Strip tag
void AddTag(char* szTag)
{
	
	char* szStoredTag = new char[64];
	strcpy(szStoredTag, szTag);

	tag_s* tag = new tag_s();
	tag->szTag = szStoredTag;

	if (!head)
	{
		head = tag;
		return;
	}

	tag_s* current = head;

	while (current->pNext)
		current = current->pNext;

	current->pNext = tag;
}

void RemoveSubstring(char* buffer, char* szStr, char* szSubstr)
{
	int start = strstr(szStr, szSubstr) - szStr;

	int len = strlen(szSubstr);

	int newStrLen = 0;
	for (int i = 0; i < len; i++)
	{
		if (!(i >= start && i < start + len))
		{
			buffer[newStrLen] = szStr[i];
			newStrLen++;
		}
	}
	buffer[newStrLen] = 0;
}

void StripTags(char* buffer, char* szName)
{
	tag_s* current = head;

	strcpy(buffer, szName);
	while (current)
	{
		
		RemoveSubstring(buffer, buffer, current->szTag);
		current = current->pNext;
	}
}

void ClearTags()
{
	tag_s* current = head;

	while (current)
	{
		tag_s* temp = current;
		current = current->pNext;
		delete temp->szTag;
		delete temp;
	}
	head = NULL;
}

