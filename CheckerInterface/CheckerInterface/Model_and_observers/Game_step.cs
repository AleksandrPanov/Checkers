﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace CheckerInterface
{
    enum StatusGame
    {
        wait,
        waitStep,
        waitEat,
        waitEatSelect,
        eating
    }
    public partial class Game : iSubject, iGame
    {
        [DllImport("C:/Users/Alyona/Documents/Visual Studio 2015/Project/Serious projects/Checkers/CheckerInterface/Checkers/bin/Debug/Checkers.dll")] 
        static extern int CallBot(int[] w_coords, int[] w_types, int w_n, int[] b_coords, int[] b_types, int b_n, int color);


        private StatusGame statusGame = StatusGame.wait;
        public bool BotStep()
        {
            int res=0;
            int[] _null = new int[1];
            _null[0] = 0;
            res = CallBot(_null, _null, 0, _null, _null, 0, (int)color);
            if ((res&1)==0) MessageBox.Show("Game Over");
            return false;
        }
        public void NextPlayer()
        {
            color = (Color)((int)color ^ 1);  
           //автоматически меняется StatusPlayer
        }
        public bool HumanStep(int x, int y) //true если ход закончен
        {
            bool isWay = board[x, y].GetIsWay();

            switch (statusGame)
            {
                case StatusGame.wait:
                    if (board[x, y].GetColor() == color)
                    {
                        SelectCheckerAndSearchWay(x, y);
                        statusGame = StatusGame.waitStep;
                    }
                    return false;
                case StatusGame.waitStep:
                    if (board[x, y].GetIsWay())
                    {
                        MoveChecker(moves.selectedChecker, x, y);
                        ClearWays();
                        statusGame = StatusGame.wait;
                        return true;
                    }
                    if (board[x, y].GetIsLight())
                        return false;
                    if (board[x, y].GetColor() == color)
                    {
                        ClearWays();
                        ClearSelected();
                        SelectCheckerAndSearchWay(x, y);
                        return false;
                    }
                    ClearWays();
                    ClearSelected();
                    statusGame = StatusGame.wait;                
                    return false;
                case StatusGame.waitEat:
                    if (board[x, y].GetIsLight())
                    {
                        SelectCheckerAndSearchEat(x, y);
                        statusGame = StatusGame.waitEatSelect;
                        return false;
                    }
                    ClearWays();
                    return false;
                case StatusGame.waitEatSelect:
                    if (board[x,y].GetIsWay())
                    {
                        if (MakeEat(moves.selectedChecker, x, y) == true)
                        {
                            ClearWays();
                            ClearSelectedCanEat();
                            statusGame = StatusGame.wait;
                            return true;
                        }
                        else
                        {
                            ClearWays();
                            ClearSelectedCanEat();
                            SelectCheckerAndSearchEat(x, y);
                            statusGame = StatusGame.eating;
                            return false;
                        }
                    }
                    if (board[x, y] == moves.selectedChecker)
                        return false;
                    if (board[x,y].GetIsLight())
                    {
                        ClearWays();
                        SelectCheckerAndSearchEat(x, y);                   
                        return false;
                    }
                    ClearWays();
                    statusGame = StatusGame.waitEat;
                    return false;

                case StatusGame.eating:
                    if (board[x, y].GetIsWay())
                    {
                        if (MakeEat(moves.selectedChecker, x, y) == true)
                        {
                            ClearWays();
                            ClearSelectedCanEat();
                            statusGame = StatusGame.wait;
                            return true;
                        }
                            ClearWays();
                            ClearSelectedCanEat();
                            SelectCheckerAndSearchEat(x, y);
                            return false;

                    }
                        return false;
            }
            return false;
        }        
        
    }
}
