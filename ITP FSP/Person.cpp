#include "Person.h"
#include "utilities.h"
#include "Company.h"

using namespace std;

void Person::mailMenu(Company& company) {
    int ch;
    do
    {
        cout << "\n\t-----Gmail-----\n";
        cout << "\t1. Compose\n";
        cout << "\t2. Inbox\n";
        cout << "\t3. Exit\n";

        cin >> ch;
        validateInput(ch, 3);
        system("CLS");
        switch (ch)
        {
        case 1:
        {
            string mail;
            cout << "\n\tEnter mail of receiver: ";
            cin.ignore();
            getline(cin, mail);
            if (mail == getMail() || !validMail(mail)) {
                cout << "\n\tYou cannot send mail to yourself or to an invalid address!!\n";
                hold("Press any key to continue: ");
                break;
            }
            Person* receiver = company.getUserByMail(mail);
            if (receiver == nullptr) {
                cout << "\n\tNo user found with this mail!!\n";
                hold("Press any key to continue: ");
                break;
            }
            Mail mailToSend = composeMail(getMail(), mail);
            company.sendMail(this, receiver, mailToSend);
            cout << "\n\tMail sent successfully!!\n";
            hold("Press any key to continue: ");
        }
        break;
        case 2:

            cout << "\n\n\t------INBOX-----\n\n";
            if (inbox.empty()) {
                cout << "\n\tNo mails in inbox!!\n";
                return;
            }
            while (1) {
                for (int i = 0; i < inbox.size(); i++) {
                    cout << "\n\n\t" << i + 1 << ": " << inbox[i].getSubject();
                    cout << "\n\t\tSender: " << inbox[i].getSender();
                    cout << "\n\t\tReceiver: " << inbox[i].getReceiver();
                }
                int mailNo;
                cout << "\n\n\tEnter mail number to read or 0 to go back: ";
                cin >> mailNo;

                if (mailNo == 0) {
                    system("CLS");
                    return;
                }

                validateInput(mailNo, int(inbox.size()));

                system("CLS");
                showMail(mailNo - 1);
                hold();
            }
            
            break;
        }

    } while (ch != 3);
}
