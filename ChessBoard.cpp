#include "ChessBoard.h"
#include "Tools.h"
#include "stdio.h"
#include "conio.h"
#include <map>
#include<stack>
map<int,char> m;
ChessBoard::ChessBoard()
{
    memset(myChessBoard,'.',sizeof(myChessBoard));
    m[BLACK] = 'x';m[WHITE] = 'o';
}
ChessBoard::~ChessBoard()
{

}
ChessBoard* ChessBoard::instance = nullptr;
ChessBoard* ChessBoard::getInstance()
{
    if(!instance)
        instance = new ChessBoard();
    return instance;
}

bool ChessBoard::PlayChess(pair<short,short> pos)
{
    if(myChessBoard[pos.first][pos.second]=='.')
        if(turn==BLACK){
            myChessBoard[pos.first][pos.second] = 'x';
            if(CheckWinner(pos))
            {
                SetCursorPos(pair<short,short>(0,16));
                cout<<"win->Press any key to stop"<<endl;
                print(pos);
                getchar();
                return false;
            }
            st.push(pos);
            turn = WHITE;
            return true;
        }
        else if(turn==WHITE){
            myChessBoard[pos.first][pos.second] = 'o';
            if(CheckWinner(pos))
            {
                SetCursorPos(pair<short,short>(0,16));
                cout<<"win->Press any key to stop"<<endl;
                print(pos);
                getchar();
                return false;
            }
            st.push(pos);
            turn = BLACK;
            return true;
        }
    return false;
}
void ChessBoard::print(pair<short,short> twinkle)
{
    for(int i = 0;i < 15;i++)
    {
        for(int j = 0;j < 15;j++)
        {
            SetCursorPos(pair<short,short>(i,j));
            cout<<myChessBoard[i][j];
        }
    }
    while(true)
    {
        Sleep(80);
        SetCursorPos(twinkle);
        cout<<"  ";
        Sleep(80);
        SetCursorPos(twinkle);
        cout<<myChessBoard[twinkle.first][twinkle.second];
        if(kbhit())
            break;
    }
}
bool ChessBoard::CheckWinner(pair<short,short> pos)
{
    if(CheckLine(pos,pair<short,short>(1,0)))return true;
    if(CheckLine(pos,pair<short,short>(0,1)))return true;
    if(CheckLine(pos,pair<short,short>(1,1)))return true;
    if(CheckLine(pos,pair<short,short>(1,-1)))return true;
    return false;
}
bool ChessBoard::CheckLine(pair<short,short> pos,pair<short,short>offset)
{
    int linkNum = 1;
    int Count = 0;
    //�ұ�
    for(int i = offset.first,j = offset.second;(pos.first+i>=0&&pos.first+i<15)&&
    (pos.second+j>=0&&pos.second+j<15);i+=offset.first,j+=offset.second)
    {
        if(myChessBoard[pos.first+i][pos.second+j]==m[turn])
        {
            linkNum++;
        }else
        {
            break;
        }
    }
    //���
    for(int i = -offset.first,j = -offset.second;(pos.first+i>=0&&pos.first+i<15)&&
    (pos.second+j>=0&&pos.second+j<15);i-=offset.first,j-=offset.second)
    {
        if(myChessBoard[pos.first+i][pos.second+j]==m[turn])
        {
            linkNum++;
        }else
        {
            break;
        }
    }
    if (linkNum > 4)
            return true;
        return false;
}
void ChessBoard::Retract()
{
    if(st.size()>=2){
        myChessBoard[st.top().first][st.top().second] = '.';
        st.pop();
        myChessBoard[st.top().first][st.top().second] = '.';
        st.pop();
    }
}
