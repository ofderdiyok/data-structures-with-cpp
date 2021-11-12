#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//declaration of protype of functions
string readToString(string, string, int*);
void destroyBalloonStreak(int*, int, int, int, int);

// reading file to string (new line = /)
string readToString(string fileName, string wholeTxt, int* lenOfLine )
{
    fstream new_file;
    new_file.open(fileName, ios::in);
    string line;
    if(!new_file){
        cout << "No such file" << endl;
    }else{
        // Use a while loop together with the getline() function to read the file line by line
        while(getline(new_file,line)){
            //output the text from file
            wholeTxt += line + "/";
            *lenOfLine = *lenOfLine + 1;
        }
        new_file.close();
    }
    return wholeTxt;
}

//part1 methods
//counter for part 1 streaks
int balloonStreak = 0;

void newValueOnArray(int* pArray, int size, int main_balloon_value, int row_of_main_balloon, int col_of_main_balloon){
    (pArray + size*row_of_main_balloon)[col_of_main_balloon] = main_balloon_value;
}

void countBalloonStreak(int* pArray, int size, int main_balloon_value, int row_of_main_balloon, int col_of_main_balloon){
    balloonStreak++;

    //sağdaki balon
    if (main_balloon_value==(pArray + size*row_of_main_balloon)[col_of_main_balloon+1]){
        balloonStreak++;

        //sağın sağı
        if(main_balloon_value==(pArray + size*row_of_main_balloon)[col_of_main_balloon+2]){
            balloonStreak++;
        }

        //sağın üstü
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon+1]){
            balloonStreak++;
        }

        //sağın altı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon+1]){
            balloonStreak++;
        }
    }

    //soldaki balon
    if (main_balloon_value==(pArray + size*row_of_main_balloon)[col_of_main_balloon-1]){
        balloonStreak++;

        //solun solu
        if(main_balloon_value==(pArray + size*row_of_main_balloon)[col_of_main_balloon-2]){
            balloonStreak++;
        }

        //solun üstü
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon-1]){
            balloonStreak++;
        }

        //solun altı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon-1]){
            balloonStreak++;
        }
    }

    //üstteki balon
    if (main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon]){
        balloonStreak++;

        //üstün üstü
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-2))[col_of_main_balloon]){
            balloonStreak++;
        }

        //üstün solu
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon-1]){
            balloonStreak++;
        }

        //üstün sağı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon+1]){
            balloonStreak++;
        }
    }

    //alttaki balon
    if (main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon]){
        balloonStreak++;

        //altın altı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+2))[col_of_main_balloon]){
            balloonStreak++;
        }

        //altın solu
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon-1]){
            balloonStreak++;
        }

        //altın sağı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon+1]){
            balloonStreak++;
        }
    }

    //streak 3 ten büyükse burası
    if (balloonStreak>=3){
        destroyBalloonStreak(pArray,size,main_balloon_value,row_of_main_balloon,col_of_main_balloon);
        balloonStreak = 0;
        main_balloon_value = main_balloon_value + 1;
        countBalloonStreak(pArray,size,main_balloon_value,row_of_main_balloon,col_of_main_balloon);
    }else{
        balloonStreak = 0;
    }
}

void destroyBalloonStreak(int* pArray, int size, int main_balloon_value, int row_of_main_balloon, int col_of_main_balloon){
    (pArray + size*row_of_main_balloon)[col_of_main_balloon] = main_balloon_value + 1;

    //sağdaki balon
    if (main_balloon_value==(pArray + size*row_of_main_balloon)[col_of_main_balloon+1]){
        (pArray + size*row_of_main_balloon)[col_of_main_balloon+1] = 0;

        //sağın sağı
        if(main_balloon_value==(pArray + size*row_of_main_balloon)[col_of_main_balloon+2]){
            (pArray + size*row_of_main_balloon)[col_of_main_balloon+2] = 0;
        }

        //sağın üstü
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon+1]){
            (pArray + size*(row_of_main_balloon-1))[col_of_main_balloon+1] = 0;
        }

        //sağın altı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon+1]){
            (pArray + size*(row_of_main_balloon+1))[col_of_main_balloon+1] = 0;
        }
    }

    //soldaki balon
    if (main_balloon_value==(pArray + size*row_of_main_balloon)[col_of_main_balloon-1]){
        (pArray + size*row_of_main_balloon)[col_of_main_balloon-1] = 0;

        //solun solu
        if(main_balloon_value==(pArray + size*row_of_main_balloon)[col_of_main_balloon-2]){
            (pArray + size*row_of_main_balloon)[col_of_main_balloon-2] = 0;
        }

        //solun üstü
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon-1]){
            (pArray + size*(row_of_main_balloon-1))[col_of_main_balloon-1] = 0;
        }

        //solun altı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon-1]){
            (pArray + size*(row_of_main_balloon+1))[col_of_main_balloon-1] = 0;
        }
    }

    //üstteki balon
    if (main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon]){
        (pArray + size*(row_of_main_balloon-1))[col_of_main_balloon] = 0;

        //üstün üstü
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-2))[col_of_main_balloon]){
            (pArray + size*(row_of_main_balloon-2))[col_of_main_balloon] = 0;
        }

        //üstün solu
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon-1]){
            (pArray + size*(row_of_main_balloon-1))[col_of_main_balloon-1] = 0;
        }

        //üstün sağı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon-1))[col_of_main_balloon+1]){
            (pArray + size*(row_of_main_balloon-1))[col_of_main_balloon+1] = 0;
        }
    }

    //alttaki balon
    if (main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon]){
        (pArray + size*(row_of_main_balloon+1))[col_of_main_balloon] = 0;

        //altın altı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+2))[col_of_main_balloon]){
            (pArray + size*(row_of_main_balloon+2))[col_of_main_balloon] = 0;
        }

        //altın solu
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon-1]){
            (pArray + size*(row_of_main_balloon+1))[col_of_main_balloon-1] = 0;
        }

        //altın sağı
        if(main_balloon_value==(pArray + size*(row_of_main_balloon+1))[col_of_main_balloon+1]){
            (pArray + size*(row_of_main_balloon+1))[col_of_main_balloon+1] = 0;
        }
    }
}

//part 2 method
void delete_same_integers(int *pSecondGameBoard, int size, int row, int col, int* pointerPoint){
    int temp_row = row;
    int temp_col = col;

    int value = (pSecondGameBoard + size*temp_row)[temp_col];
    *pointerPoint += value;
    (pSecondGameBoard + size*temp_row)[temp_col] = 0;
    //cout << "giristeki ana deger yakildi ve Value: " << value << " total point: "<< *pointerPoint << endl;

    //dikey ve yatay çizgiler için.
    for (int i = 0; i < size; i++) {
        if ((pSecondGameBoard + size*i)[temp_col]==value){
            (pSecondGameBoard + size*i)[temp_col] = 0;
            *pointerPoint += value;
        }

        if ((pSecondGameBoard + size*temp_row)[i]==value){
            (pSecondGameBoard + size*temp_row)[i] = 0;
            *pointerPoint += value;
        }
    }

    temp_col = col;
    temp_row = row;
    //cout << "yatay ve dikeyler yakildi ve Value: " << value << " total point: "<< *pointerPoint << endl;

    // sağ aşağı hareketleri kontrol edecez
    while(temp_row < size && temp_col < size){ //sınırları kontrol edecez
        if ((pSecondGameBoard + size*temp_row)[temp_col]==value){
            (pSecondGameBoard + size*temp_row)[temp_col] = 0;
            *pointerPoint += value;
        }
        temp_row = temp_row + 1;
        temp_col = temp_col + 1;
    }

    //cout << "sag asagidakiler yakildi ve Value: " << value << " total point: "<< *pointerPoint << endl;

    temp_col = col;
    temp_row = row;

    // sol yukarı hareketleri kontrol edecez
    while(temp_row >= 0 && temp_col >= 0){ //sınırları kontrol edecez
        if ((pSecondGameBoard + size*temp_row)[temp_col]==value){
            (pSecondGameBoard + size*temp_row)[temp_col] = 0;
            *pointerPoint += value;
        }
        temp_row = temp_row - 1;
        temp_col = temp_col - 1;
    }
    //cout << "sol yukaridakiler yakildi ve Value: " << value << " total point: "<< *pointerPoint << endl;

    temp_col = col;
    temp_row = row;

    // sol aşağı kontrol edecez
    while (temp_row < size && temp_col >= 0){ //sınırları kontrol edecez
        if ((pSecondGameBoard + size*temp_row)[temp_col]==value){
            (pSecondGameBoard + size*temp_row)[temp_col] = 0;
            *pointerPoint += value;
        }
        temp_row = temp_row + 1;
        temp_col = temp_col - 1;
    }

    //cout << "sol asagidakiler yakildi ve Value: " << value << " total point: "<< *pointerPoint << endl;

    temp_col = col;
    temp_row = row;

    // sağ yukarı kontrol ecez
    while(temp_row >= 0 && temp_col < size){ //sınırları kontrol edecez
        if ((pSecondGameBoard + size*temp_row)[temp_col]==value){
            (pSecondGameBoard + size*temp_row)[temp_col] = 0;
            *pointerPoint += value;
        }
        temp_row = temp_row - 1;
        temp_col = temp_col + 1;
    }
    //cout << "sag yukaridakiler yakildi ve Value: " << value << " total point: "<< *pointerPoint << endl;
}

int main(int argc, char *argv[]) {
    //file names variables
    //string fileForFirstPart = argv[1];
    //string fileForSecondPart = argv[2];
    //string fileForOutput = argv[3];

    string fileForFirstPart = "input1.txt";
    string fileForSecondPart = "input2.txt";
    string fileForOutput = "output.txt";

    //declaration for the first part
    string wholeTxtFirstPart = "";

    int* pointer_length_of_the_line_for_the_first_part;
    int length_of_the_line_for_the_first_part = 0; //length of the line for the first part
    pointer_length_of_the_line_for_the_first_part = &length_of_the_line_for_the_first_part;

    int* pointer_size_of_first_parts_game_board;
    int size_of_first_parts_game_board = 0;
    pointer_size_of_first_parts_game_board = &size_of_first_parts_game_board;

    wholeTxtFirstPart = readToString(fileForFirstPart,wholeTxtFirstPart,pointer_length_of_the_line_for_the_first_part);
    string lines_part1[length_of_the_line_for_the_first_part];

    int num_of_lines_part_1 = 0;
    string line_for_part_1;
    ifstream temp_file(fileForFirstPart);
    if(temp_file.is_open())
    {
        while(!temp_file.eof())
        {
            getline(temp_file,line_for_part_1);
            lines_part1[num_of_lines_part_1] = line_for_part_1;
            num_of_lines_part_1 = num_of_lines_part_1 + 1;
        }
        temp_file.close();
    }

    size_of_first_parts_game_board = stoi(lines_part1[0]);

    //initalizing array
    int first_parts_game_board[size_of_first_parts_game_board][size_of_first_parts_game_board];
    for (int i = 0; i < size_of_first_parts_game_board; ++i) {
        for (int j = 0; j < size_of_first_parts_game_board; ++j) {
            first_parts_game_board[i][j] = 0;
        }
    }

    int *pArray = first_parts_game_board[0];

    for (int star = 1; star < length_of_the_line_for_the_first_part; star++) {

        string array_for_first_part_commands[3];
        int num_for_first_part_limit = 0;
        stringstream ssin(lines_part1[star]);
        while(ssin.good() && num_for_first_part_limit < 3){
            ssin >> array_for_first_part_commands[num_for_first_part_limit];
            ++num_for_first_part_limit;
        }

        int new_value = stoi(array_for_first_part_commands[0]);
        int new_row = stoi(array_for_first_part_commands[1]);
        int new_col = stoi(array_for_first_part_commands[2]);

        newValueOnArray(pArray, size_of_first_parts_game_board,new_value,new_row,new_col);
        countBalloonStreak(pArray,size_of_first_parts_game_board,new_value,new_row,new_col);
    }

    //part 2 kısımları başlıyor
    string text2 = "";

    int* pointer_length_of_the_line_for_the_second_part;
    int length_of_the_line_for_the_second_part = 0; //length of the line for the second part
    pointer_length_of_the_line_for_the_second_part = &length_of_the_line_for_the_second_part;

    text2 = readToString(fileForSecondPart,text2,pointer_length_of_the_line_for_the_second_part);
    string lines_part_2[length_of_the_line_for_the_second_part];

    int counter = 0;
    string line;
    ifstream file(fileForSecondPart);
    if(file.is_open())
    {
        while(!file.eof())
        {
            getline(file,line);
            lines_part_2[counter] = line;
            counter = counter + 1;
        }
        file.close();
    }

    int* pointer_size_of_second_parts_game_board;
    int size_of_second_parts_game_board = 0;
    pointer_size_of_second_parts_game_board = &size_of_second_parts_game_board;
    size_of_second_parts_game_board = stoi(lines_part_2[0]);

    int* pointer_point;
    int point = 0; //l
    pointer_point = &point;

    int second_parts_game_board[size_of_second_parts_game_board][size_of_second_parts_game_board];

    for (int numerator = 1; numerator < size_of_second_parts_game_board + 1; ++numerator) {
        string arrayForMatrix2[size_of_second_parts_game_board];
        int numForMatrix2 = 0;
        stringstream ssin(lines_part_2[numerator]);
        while(ssin.good() && numForMatrix2 < size_of_second_parts_game_board){
            ssin >> arrayForMatrix2[numForMatrix2];
            ++numForMatrix2;
        }
        for (int j = 0; j < size_of_second_parts_game_board; ++j) {
            second_parts_game_board[numerator-1][j] = stoi(arrayForMatrix2[j]);
        }
    }

    int *p_second_game_board = second_parts_game_board[0];

    for (int numerator = size_of_second_parts_game_board + 1 ; numerator < length_of_the_line_for_the_second_part; ++numerator) {
        string arrayForMatrix2[2];
        int numForMatrix2 = 0;
        stringstream ssin(lines_part_2[numerator]);
        while(ssin.good() && numForMatrix2 < 2){
            ssin >> arrayForMatrix2[numForMatrix2];
            ++numForMatrix2;
        }

        int dim_x = stoi(arrayForMatrix2[0]);
        int dim_y = stoi(arrayForMatrix2[1]);

        delete_same_integers(p_second_game_board,size_of_second_parts_game_board,dim_x, dim_y, pointer_point);
    }

    //dosyaya yazma  işlemleri yapılacak
    ofstream myfile;
    myfile.open (fileForOutput);
    myfile << "PART 1:\n";

    for (int i = 0; i < size_of_first_parts_game_board; i++) {
        for (int j = 0; j < size_of_first_parts_game_board; j++) {
            myfile << (pArray + size_of_first_parts_game_board*i)[j] << " ";
        }
        myfile << "\n";
    }

    myfile << "\nPART 2:\n";

    for (int i = 0; i < size_of_second_parts_game_board; ++i) {
        for (int j = 0; j < size_of_second_parts_game_board; ++j) {
            myfile << second_parts_game_board[i][j] << " ";
        }
        myfile << "\n";
    }
    myfile << "Final Point: " << *pointer_point <<"p";
    myfile.close();

    return 0;
}