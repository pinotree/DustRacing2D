// This file is part of Dust Racing 2D.
// Copyright (C) 2011 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QHBoxLayout>

#include "game.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "settings.hpp"

#include <MCException>
#include <MCLogger>

int main(int argc, char ** argv)
{
    try
    {
        Settings settings;

        // Create the QApplication
        QApplication::setGraphicsSystem("opengl");
        QApplication app(argc, argv);

        // Initialize the logger
        QString logPath = QDir::tempPath() + QDir::separator() + "dustrac.log";
        MCLogger::init(logPath.toStdString().c_str());
        MCLogger::setEchoMode(true);
        MCLogger::setDateTime(true);

        int hRes, vRes;
        bool fullScreen;
        Settings::instance().loadResolution(hRes, vRes, fullScreen);
        MCLogger().info() << "Resolution: " << hRes << " " << vRes << " " << fullScreen;

        // Create the main window / renderer
        MCLogger().info() << "Creating the renderer..";
        Renderer renderer(hRes, vRes, fullScreen);
        renderer.activateWindow();

        if (fullScreen)
        {
            // Adjust scene height so that window aspect ratio is taken into account.
            const int newSceneHeight =
                Scene::width() * QApplication::desktop()->height() / QApplication::desktop()->width();
            Scene::setSize(Scene::width(), newSceneHeight);

            renderer.showFullScreen();
        }
        else
        {
            // Adjust scene height so that window aspect ratio is taken into account.
            const int newSceneHeight = Scene::width() * vRes / hRes;
            Scene::setSize(Scene::width(), newSceneHeight);

            renderer.show();
        }

        renderer.setFocus();
        renderer.setCursor(Qt::BlankCursor);

        // Create the game object and set the renderer
        MCLogger().info() << "Creating game object..";
        Game game;
        game.setRenderer(&renderer);
        game.setTargetUpdateFps(60);
        game.connect(&renderer, SIGNAL(closed()), &game, SLOT(finish()));

        // Initialize and start the game
        if (game.init())
        {
            game.start();
        }
        else
        {
            MCLogger().fatal() << "Initing the game failed.";
            return EXIT_FAILURE;
        }

        return app.exec();
    }
    // Catch some errors during game initialization e.g.
    // a vertex shader not found.
    catch (MCException & e)
    {
        MCLogger().fatal() << e.what();
        return EXIT_FAILURE;
    }
}
