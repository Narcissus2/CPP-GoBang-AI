#include "AIPlayer1.h"
#include<iostream>
#include<ctime>
#include<map>
#include"Tools.h"
using namespace std;


AIPlayer1::AIPlayer1(ChessType Color)
{

    chessColor = Color;
    toScore["_a_"]=10;
    toScore["a_"]=5;
    toScore["_a"]=5;

    toScore["_aa_"]=100;
    toScore["aa_"]=50;
    toScore["_aa"]=50;

    toScore["_aaa_"]=1000;
    toScore["aaa_"]=500;
    toScore["_aaa"]=500;

    toScore["_aaaa_"]=10000;
    toScore["aaaa_"]=5000;
    toScore["_aaaa"]=5000;

    toScore["aaaaa"]=FLT_MAX;
    toScore["aaaaa_"]=FLT_MAX;
    toScore["_aaaaa"]=FLT_MAX;
    toScore["_aaaaa_"]=FLT_MAX;
    stateMap[BLACK] = 'x';stateMap[WHITE] = 'o';
}
AIPlayer1::AIPlayer1()
{

}
AIPlayer1::~AIPlayer1()
{

}
void AIPlayer1::playChess()
{
    HideCursor();
    temp = chessColor;
    if(ChessBoard::getInstance()->st.size()==0)
    {
        ChessBoard::getInstance()->st.push(pair<short,short>(7,7));
        ChessBoard::getInstance()->myChessBoard[7][7] = stateMap[temp];
        ChessBoard::getInstance()->turn = ChessType(-temp+3);
        return ;
    }
    else if(ChessBoard::getInstance()->st.size()==1)
    {
        for(int i = 0;i < 15;i++)
            for(int j = 0;j < 15;j++){
                if(ChessBoard::getInstance()->myChessBoard[i][j] == ChessBoard::getInstance()->m[int(-chessColor+3)])
                {
                    srand((unsigned)time(NULL));
                    int a=1,b=1;
                    while(a==0&&b==0)
                        a = rand()%3-1;b = rand()%3-1;
                    ChessBoard::getInstance()->myChessBoard[i+a][j+b] = ChessBoard::getInstance()->m[int(chessColor)];
                    ChessBoard::getInstance()->turn = ChessType(-temp+3);
                    ChessBoard::getInstance()->st.push(pair<short,short>(i+a,j+b));
                    return ;
                }
            }
    }
    memset(Score,0,sizeof(Score));//first step set all the zero
    float Max = -1;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(ChessBoard::getInstance()->myChessBoard[i][j]=='.')
            {
                Score[i][j] = getTotalScore(pair<short,short>(i,j));
                SetCursorPos(pair<short,short>((i+10)*2,j));
                //print all the score
                cout<<"   ";
                //Sleep(1);
                SetCursorPos(pair<short,short>((i+10)*2,j));
                cout<<Score[i][j];
                Max = max(Max,Score[i][j]);
            }
        }
    }
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if(Max==Score[i][j])
            {
                //直接调用playchess，所有判断执行函数已经封装在playchess内了
                ChessBoard::getInstance()->PlayChess(pair<short,short>(i,j));
                return ;
            }
        }
    }
}
float AIPlayer1::getTotalScore(pair<short,short> p)
{
    float ans = 0;
    ans += getLineScore(p,pair<short,short>(1,0),temp);
    ans += getLineScore(p,pair<short,short>(0,1),temp);
    ans += getLineScore(p,pair<short,short>(1,1),temp);
    ans += getLineScore(p,pair<short,short>(1,-1),temp);

    ans += getLineScore(p,pair<short,short>(1,0),ChessType(-temp+3));
    ans += getLineScore(p,pair<short,short>(0,1),ChessType(-temp+3));
    ans += getLineScore(p,pair<short,short>(1,1),ChessType(-temp+3));
    ans += getLineScore(p,pair<short,short>(1,-1),ChessType(-temp+3));

    return ans;
}
float AIPlayer1::getLineScore(pair<short,short> p,pair<short,short> offset,ChessType myChessColor)
{
    string str = "a";
    //×ó±ß
    for(int i = offset.first,j = offset.second; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15; i+=offset.first,j+=offset.second)
    {
        if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]==stateMap[myChessColor])
        {
            str+="a";
        }
        else if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]=='.')
        {
            str+="_";
            break;
        }
        else
        {
            break;
        }
    }
    for(int i = -offset.first,j = -offset.second; p.first+i>=0&&p.first+i<15
            &&p.second+j>=0&&p.second+j<15; i-=offset.first,j-=offset.second)
    {
        if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]==stateMap[myChessColor])
        {
            str="a"+str;
        }
        else if(ChessBoard::getInstance()->myChessBoard[p.first+i][p.second+j]=='.')
        {
            str="_"+str;
            break;
        }
        else
        {
            break;
        }
    }

    //Sleep(1);
    return toScore[str];

}
