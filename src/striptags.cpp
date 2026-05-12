#include "stdafx.h"

struct tag_s {
    tag_s *pNext;
    char *szTag;
};

tag_s *head = nullptr;

// Strip tag
void AddTag(char *szTag) {
    char *szStoredTag = new char[64];
    strcpy(szStoredTag, szTag);

    auto *tag = new tag_s();
    tag->szTag = szStoredTag;

    if (head == nullptr) {
        head = tag;
        return;
    }

    tag_s *current = head;

    while (current->pNext != nullptr) {
        current = current->pNext;
    }

    current->pNext = tag;
}

void RemoveSubstring(char *buffer, char *szStr, char *szSubstr) {
    char *match = strstr(szStr, szSubstr);
    if (match == nullptr) {
        return; // Always check if tag exists
    }

    int start = match - szStr;
    int subLen = strlen(szSubstr);
    int strLen = strlen(szStr); // <--- Need this

    int newStrLen = 0;
    for (int i = 0; i < strLen; i++) { // Loop through the WHOLE name
        if (i < start || i >= start + subLen) {
            buffer[newStrLen] = szStr[i];
            newStrLen++;
        }
    }
    buffer[newStrLen] = '\0';
}

void StripTags(char *buffer, char *szName) {
    tag_s *current = head;

    strcpy(buffer, szName);
    while (current != nullptr) {
        RemoveSubstring(buffer, buffer, current->szTag);
        current = current->pNext;
    }
}

void ClearTags() {
    tag_s *current = head;

    while (current != nullptr) {
        tag_s *temp = current;
        current = current->pNext;
        delete temp->szTag;
        delete temp;
    }
    head = nullptr;
}
