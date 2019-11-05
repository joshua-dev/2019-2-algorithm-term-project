#include "Map.h"

// 기본 생성자는 map과 default_map을 Null space로 채운다.
Map::Map()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            this->map[i][j] = 4;
            this->default_map[i][j] = 4;
        }
    }
}

/*  
복사 생성자는 main()에서 선언된 2차원 배열 map_of_stage를 map과 default_map에 복사
목적지의 갯수를 numDest에 저장
Step 횟수와 Push 횟수를 0으로 초기화
*/
Map::Map(int map_of_stage[10][10])
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            this->map[i][j] = map_of_stage[i][j];
            this->default_map[i][j] = map_of_stage[i][j];
        }
    }
    countDest();
    numStep = 0;
    numPush = 0;
}

// map의 (target_x, target_y) 위치의 값을 input으로 변경
Map &Map::setElement(int target_x, int target_y, int input)
{
    this->map[target_x][target_y] = input;
    return *this;
}

// 캐릭터의 위치를 (target_x, target_y)로 설정
Map &Map::setCharacter(int target_x, int target_y)
{
    this->map[target_x][target_y] = 5;
    return *this;
}

Map &Map::move(char arrow)
{
    /*  
    arrow input -> move
    front of wall, or over 2 box -> don't move
    front of one box and not blocked -> move with box
    */

    find_character();                              // 캐릭터 현재 위치 탐색
    int char_row = this->location_of_character[0]; // 캐릭터의 현재 위치(행 값)
    int char_col = this->location_of_character[1]; // 캐릭터의 현재 위치(열 값)

    switch (arrow)
    {
    /*
        Unicode 72 represents 'up'
        Unicode 75 represents 'left'
        Unicode 77 represents 'right'
        Unicode 80 represents 'down'
        */
    case 72: // ↑ 입력
        if ((this->map[char_row - 1][char_col] == 0) || (this->map[char_row - 1][char_col] == 3))
        { // 캐릭터 위쪽이 비어있거나 목적지이면 캐릭터를 위쪽으로 한칸 전진
            setCharacter(char_row - 1, char_col);
            setElement(char_row, char_col, default_map[char_row][char_col]);
            increaseNumStep();
        }
        else if (this->map[char_row - 1][char_col] == 1)
        {                 // 캐릭터 위쪽이 벽이면
            do_nothing(); // 캐릭터 이동 불가능
        }
        else if (this->map[char_row - 1][char_col] == 2)
        { // 캐릭터 위쪽이 박스일 때
            if ((this->map[char_row - 2][char_col] == 1) || (this->map[char_row - 2][char_col] == 2))
            {                 // 박스 위쪽이 벽이거나 박스이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row - 2][char_col] == 0)
            {                                                                    // 박스 앞이 비어있으면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row - 1, char_col);                            // 캐릭터와 박스가 함께 위쪽으로 이동
                setElement(char_row - 2, char_col, 2);
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row - 2][char_col] == 3)
            {                                                                    // 박스 앞이 목적지이면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row - 1, char_col);                            // 캐릭터와 박스가 함께 위쪽으로 이동
                setElement(char_row - 2, char_col, 6);                           // 목적지에 박스가 들어갔음을 표시
                increaseNumStep();
                increaseNumPush();
            }
        }
        else if (this->map[char_row - 1][char_col] == 6)
        { // 캐릭터 위쪽이 BoxOnDest이면
            if (this->map[char_row - 2][char_col] == 0)
            {                                                                    // BoxOnDest 앞이 비어있으면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row - 1, char_col);
                setElement(char_row - 2, char_col, 2);
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row - 2][char_col] == 1)
            {                 // BoxOnDest 앞이 벽이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row - 2][char_col] == 2)
            {                 // BoxOnDest 앞이 박스이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row - 2][char_col] == 3)
            {                                                                    // BoxOnDest 앞이 목적지이면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row - 1, char_col);                            // 캐릭터 한칸 전진
                setElement(char_row - 2, char_col, 6);                           // 박스도 한칸 전진
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row - 2][char_col] == 6)
            { // BoxOnDest 앞이 BoxOnDest이면
                do_nothing();
            }
        }
        break;

    case 75: // <- 입력
        if ((this->map[char_row][char_col - 1] == 0) || (this->map[char_row][char_col - 1] == 3))
        { // 캐릭터 왼쪽이 비어있거나 목적지이면 캐릭터를 왼쪽으로 한칸 전진
            setCharacter(char_row, char_col - 1);
            setElement(char_row, char_col, default_map[char_row][char_col]);
            increaseNumStep();
        }
        else if (this->map[char_row][char_col - 1] == 1)
        {                 // 캐릭터 왼쪽이 벽이면
            do_nothing(); // 캐릭터 이동 불가능
        }
        else if (this->map[char_row][char_col - 1] == 2)
        { // 캐릭터 왼쪽이 박스일 때
            if ((this->map[char_row][char_col - 2] == 1) || (this->map[char_row][char_col - 2] == 2))
            {                 // 박스 왼쪽이 벽이거나 박스이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row][char_col - 2] == 0)
            {                                                                    // 박스 앞이 비어있으면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row, char_col - 1);                            // 캐릭터와 박스가 함께 왼쪽으로 이동
                setElement(char_row, char_col - 2, 2);
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row][char_col - 2] == 3)
            {                                                                    // 박스 앞이 목적지이면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row, char_col - 1);                            // 캐릭터와 박스가 함께 왼쪽으로 이동
                setElement(char_row, char_col - 2, 6);                           // 목적지에 박스가 들어갔음을 표시
                increaseNumStep();
                increaseNumPush();
            }
        }
        else if (this->map[char_row][char_col - 1] == 6)
        { // 캐릭터 왼쪽이 BoxOnDest이면
            if (this->map[char_row][char_col - 2] == 0)
            {                                                                    // BoxOnDest 앞이 비어있으면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row, char_col - 1);
                setElement(char_row, char_col - 2, 2);
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row][char_col - 2] == 1)
            {                 // BoxOnDest 앞이 벽이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row][char_col - 2] == 2)
            {                 // BoxOnDest 앞이 박스이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row][char_col - 2] == 3)
            {                                                                    // BoxOnDest 앞이 목적지이면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row, char_col - 1);                            // 캐릭터 한칸 전진
                setElement(char_row, char_col - 2, 6);                           // 박스도 한칸 전진
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row][char_col - 2] == 6)
            { // BoxOnDest 앞이 BoxOnDest이면
                do_nothing();
            }
        }
        break;

    case 77: // -> 입력
        if ((this->map[char_row][char_col + 1] == 0) || (this->map[char_row][char_col + 1] == 3))
        { // 캐릭터 오른쪽이 비어있거나 목적지이면 캐릭터를 오른쪽으로 한칸 전진
            setCharacter(char_row, char_col + 1);
            setElement(char_row, char_col, default_map[char_row][char_col]);
            increaseNumStep();
        }
        else if (this->map[char_row][char_col + 1] == 1)
        {                 // 캐릭터 오른쪽이 벽이면
            do_nothing(); // 캐릭터 이동 불가능
        }
        else if (this->map[char_row][char_col + 1] == 2)
        { // 캐릭터 오른쪽이 박스일 때
            if ((this->map[char_row][char_col + 2] == 1) || (this->map[char_row][char_col + 2] == 2))
            {                 // 박스 오른쪽이 벽이거나 박스이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row][char_col + 2] == 0)
            {                                                                    // 박스 앞이 비어있으면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row, char_col + 1);                            // 캐릭터와 박스가 함께 오른쪽으로 이동
                setElement(char_row, char_col + 2, 2);
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row][char_col + 2] == 3)
            {                                                                    // 박스 앞이 목적지이면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row, char_col + 1);                            // 캐릭터와 박스가 함께 오른쪽으로 이동
                setElement(char_row, char_col + 2, 6);                           // 목적지에 박스가 들어갔음을 표시
                increaseNumStep();
                increaseNumPush();
            }
        }
        else if (this->map[char_row][char_col + 1] == 6)
        { // 캐릭터 위쪽이 BoxOnDest이면
            if (this->map[char_row][char_col + 2] == 0)
            {                                                                    // BoxOnDest 앞이 비어있으면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row, char_col + 1);
                setElement(char_row, char_col + 2, 2);
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row][char_col + 2] == 1)
            {                 // BoxOnDest 앞이 벽이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row][char_col + 2] == 2)
            {                 // BoxOnDest 앞이 박스이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row][char_col + 2] == 3)
            {                                                                    // BoxOnDest 앞이 목적지이면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row, char_col + 1);                            // 캐릭터 한칸 전진
                setElement(char_row, char_col + 2, 6);                           // 박스도 한칸 전진
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row][char_col + 2] == 6)
            { // BoxOnDest 앞이 BoxOnDest이면
                do_nothing();
            }
        }
        break;

    case 80: // ↓ 입력
        if ((this->map[char_row + 1][char_col] == 0) || (this->map[char_row + 1][char_col] == 3))
        { // 캐릭터 아래쪽이 비어있거나 목적지이면 캐릭터를 아래쪽으로 한칸 전진
            setCharacter(char_row + 1, char_col);
            setElement(char_row, char_col, default_map[char_row][char_col]);
            increaseNumStep();
        }
        else if (this->map[char_row + 1][char_col] == 1)
        {                 // 캐릭터 아래쪽이 벽이면
            do_nothing(); // 캐릭터 이동 불가능
        }
        else if (this->map[char_row + 1][char_col] == 2)
        { // 캐릭터 아래쪽이 박스일 때
            if ((this->map[char_row + 2][char_col] == 1) || (this->map[char_row + 2][char_col] == 2))
            {                 // 박스 아래쪽이 벽이거나 박스이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row + 2][char_col] == 0)
            {                                                                    // 박스 앞이 비어있으면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row + 1, char_col);                            // 캐릭터와 박스가 함께 아래쪽으로 이동
                setElement(char_row + 2, char_col, 2);
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row + 2][char_col] == 3)
            {                                                                    // 박스 앞이 목적지이면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row + 1, char_col);                            // 캐릭터와 박스가 함께 아래쪽으로 이동
                setElement(char_row + 2, char_col, 6);                           // 목적지에 박스가 들어갔음을 표시
                increaseNumStep();
                increaseNumPush();
            }
        }
        else if (this->map[char_row + 1][char_col] == 6)
        { // 캐릭터 위쪽이 BoxOnDest이면
            if (this->map[char_row + 2][char_col] == 0)
            {                                                                    // BoxOnDest 앞이 비어있으면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row + 1, char_col);
                setElement(char_row + 2, char_col, 2);
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row + 2][char_col] == 1)
            {                 // BoxOnDest 앞이 벽이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row + 2][char_col] == 2)
            {                 // BoxOnDest 앞이 박스이면
                do_nothing(); // 캐릭터 이동 불가능
            }
            else if (this->map[char_row + 2][char_col] == 3)
            {                                                                    // BoxOnDest 앞이 목적지이면
                setElement(char_row, char_col, default_map[char_row][char_col]); // 캐릭터 있던 곳은 기본 값
                setCharacter(char_row + 1, char_col);                            // 캐릭터 한칸 전진
                setElement(char_row + 2, char_col, 6);                           // 박스도 한칸 전진
                increaseNumStep();
                increaseNumPush();
            }
            else if (this->map[char_row + 2][char_col] == 6)
            { // BoxOnDest 앞이 BoxOnDest이면
                do_nothing();
            }
        }
        break;
    } // end switch-case
    countBoxOnDest();
    return *this;
}

// Search location of character and store it to location_of_character
Map &Map::find_character()
{
    int row, col;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (this->map[i][j] == 5)
            {
                row = i;
                col = j;
            }
        }
    }
    this->location_of_character[0] = row;
    this->location_of_character[1] = col;
    return *this;
}

// If character cannot move, just let it be
Map &Map::do_nothing()
{
    return *this;
}

// Counts number of destinations
Map &Map::countDest()
{
    this->numDest = 0;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (this->default_map[i][j] == 3)
            {
                this->numDest++;
            }
        }
    }
    return *this;
}

// Counts number of boxes on destination
Map &Map::countBoxOnDest()
{
    this->numBoxOnDest = 0;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (this->map[i][j] == 6)
            {
                this->numBoxOnDest++;
            }
        }
    }
    return *this;
}

Map &Map::increaseNumStep()
{
    this->numStep++;
    return *this;
}

Map &Map::increaseNumPush()
{
    this->numPush++;
    return *this;
}
