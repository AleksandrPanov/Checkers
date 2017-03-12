﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CheckerInterface.View;

namespace CheckerInterface
{
    public class Controller : iController
    {
        iGame game_model;
        Form1 form_view;
        SettingForm settingForm;

        public Controller(Game game, iSubject game_observer)
        {
            this.game_model = game;
            form_view = new Form1(this, game);
            game_observer.registerObserver(form_view);

            Application.EnableVisualStyles();
           //Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(form_view);
        }

        public void buttonOnePlayer()
        {
            form_view.VisibleButtons(false);
            game_model.ClearResource();
            form_view.CreateBoard();
            game_model.FillBoardAndListCheckers();
            game_model.SetGame(StatusApplication.game, Color.white, StatusPlayer.human, StatusPlayer.bot, StatusGame.wait);
            /*game_model.SetStatusApplication(StatusApplication.game);
            game_model.SetStatusPlayers(StatusPlayer.human, StatusPlayer.bot);
            game_model.SetStartColor(Color.white);
            game_model.SetStatusGame(StatusGame.wait);*/
            game_model.StartGame();
        }
        public void buttonTwoPlayers()
        {
            form_view.VisibleButtons(false);
            game_model.ClearResource();
            form_view.CreateBoard();
            game_model.FillBoardAndListCheckers();
            game_model.SetGame(StatusApplication.game, Color.white, StatusPlayer.human, StatusPlayer.human, StatusGame.wait);
            /*game_model.SetStatusApplication(StatusApplication.game);
            game_model.SetStatusPlayers(StatusPlayer.human, StatusPlayer.human);
            game_model.SetStartColor(Color.white);
            game_model.SetStatusGame(StatusGame.wait);*/
            game_model.StartGame();
        }
        public void buttonLoadGame()
        {
            form_view.VisibleButtons(false);
        }
        public void buttonConstrutor()
        {
            form_view.VisibleButtons(false);
            game_model.ClearResource();
            game_model.ClearResource();
            game_model.SetStartColor(Color.empty);
            form_view.CreateBoard();
            game_model.SetStatusApplication(StatusApplication.constructor);
            form_view.panel2.Visible = true;
        }
        public void buttonSetting()
        {
            form_view.VisibleButtons(false);
        }

        public void buttonAddChecker()
        {
            form_view.SetCheckedButDelete(false);
            if (form_view.RadiosButtonsIsChecked())
                form_view.SetColorButton(System.Drawing.Color.White, System.Drawing.Color.Gray);
            else form_view.SetColorButton(System.Drawing.Color.Gray, System.Drawing.Color.Gray);
        }
        public void buttonDeleteChecker()
        {
            form_view.SetCheckedButDelete(true);
            form_view.SetColorButton(System.Drawing.Color.Gray, System.Drawing.Color.White);
        }
        public void buttonPlayInConstructor()
        {
            form_view.panel2.Visible = false;
            //реализация окна заполнения настроек
            settingForm = new SettingForm(this);
            settingForm.Show();
            //реализация окна заполнения настроек

           /* game_model.SetStatusApplication(StatusApplication.game);
            game_model.SetStatusPlayers(StatusPlayer.human, StatusPlayer.human);
            game_model.SetStartColor(Color.white);
            game_model.SetStatusGame(StatusGame.wait);
            if (game_model.SearchEatingAndWriteToMove())
                game_model.SetStatusGame(StatusGame.waitEat);*/
        }
        public void buttonPlaySetting()
        {
           if (settingForm.CanStartGame())
            {
                game_model.SetGame(StatusApplication.game, settingForm.GetColorPlayer1(), settingForm.GetStatusPl1(), settingForm.GetStatusPl2(), StatusGame.wait);
                /*game_model.SetStatusApplication(StatusApplication.game);
                game_model.SetStartColor(settingForm.GetColorPlayer1());
                game_model.SetStatusPlayers(settingForm.GetStatusPl1(), settingForm.GetStatusPl2());
                game_model.SetStatusGame(StatusGame.wait);*/
                if ((game_model.GetStatusPlayer()==StatusPlayer.human)&&(game_model.SearchEatingAndWriteToMove()))
                    game_model.SetStatusGame(StatusGame.waitEat);
                settingForm.Close();
                game_model.StartGame();
            }
        }
        public void buttonBotVSBot()
        {
            form_view.VisibleButtons(false);
            game_model.ClearResource();
            form_view.CreateBoard();
            game_model.FillBoardAndListCheckers();
            game_model.SetGame(StatusApplication.game, Color.white, StatusPlayer.bot, StatusPlayer.bot, StatusGame.wait);
            game_model.StartGame();
        }

        public void ClickCell(int x, int y)
        {
            switch (game_model.GetStatusApplication())
            {
                case StatusApplication.game:
                    if (game_model.GetStatusPlayer() == StatusPlayer.human)
                    {
                        if (game_model.HumanStep(x, y) == true)
                        {
                            game_model.NextPlayer();

                            if (game_model.SearchAnyMove()) //есть ходы?
                                switch (game_model.GetStatusPlayer()) //да
                                {
                                    case StatusPlayer.human:
                                        // надо ли есть?
                                        if (game_model.SearchEatingAndWriteToMove())
                                            game_model.SetStatusGame(StatusGame.waitEat);
                                        return;

                                    case StatusPlayer.bot:
                                        //включили таймер
                                        form_view.timer.Enabled = true;
                                        return;
                                }
                            else
                            {
                                //нет: конец игры
                                MessageBox.Show("Game over");
                                return;
                            }
                        }
                    }
                    break;
                case StatusApplication.constructor:
                    if (form_view.RadiosButtonsIsChecked() && !form_view.IsCheckedButtonDelete())
                    {
                        if ((x + y) % 2 == 1)
                        {
                            game_model.DeleteChecker(x, y);
                            game_model.CreateChecker(new Checker(form_view.GetChosenColor(), form_view.GetChosenFigure(), x, y));
                        }
                    }
                    else if (form_view.IsCheckedButtonDelete())
                        game_model.DeleteChecker(x, y);
                    break;
                default: MessageBox.Show("Error, status != game or constructor, status == "+ game_model.GetStatusApplication().ToString()); break;
            }

        }

        public void Time()
        {
            if (game_model.GetStatusPlayer() == StatusPlayer.bot)
            {
                if (game_model.BotStep() == true)
                {
                    game_model.NextPlayer();

                    if (game_model.SearchAnyMove()) //есть ходы?
                        switch (game_model.GetStatusPlayer()) //да
                        {
                            case StatusPlayer.human:
                                //выключили таймер
                                form_view.timer.Enabled = false;
                                // надо ли есть?
                                if (game_model.SearchEatingAndWriteToMove())
                                    game_model.SetStatusGame(StatusGame.waitEat);
                                return;

                            //если бот, то ничего не делаем
                        }
                    else
                    {
                        //нет: конец игры
                        MessageBox.Show("Game over");
                        return;
                    }
                }
            }

        }

        public void keyEsc()
        {
            form_view.VisibleButtons(true);
            form_view.panel2.Visible = false;
        }
    }
}
