#pragma once
#include<iostream>
#include<string>
using namespace std;
class Mail
{
private:
	string Email;
    string sender;
    string receiver;
    string subject;
    string body;
public:
    Mail() {}

    Mail(string s, string r, string sub, string b)
    {
        sender = s;
        receiver = r;
        subject = sub;
        body = b;
    }
    void PrepareMail(string s, string r, string sub, string b)
    {
        sender = s;
        receiver = r;
        subject = sub;
        body = b;
    }

    string getSender() { return sender; }
    string getReceiver() { return receiver; }
    string getSubject() { return subject; }
    string getBody() { return body; }


};

