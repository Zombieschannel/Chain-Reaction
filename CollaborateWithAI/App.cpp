#include "App.h"

void App::Start()
{

   
    window.setTitle(AppName);
    textures.AddTexture("Res/player.png", "player");
    textures.AddTexture("Res/PowerUps.png", "power");
    textures.AddTexture("Res/Life.png", "life");
    textures.AddTexture("Res/Bullet.png", "bullet");
    textures.AddTexture("Res/Speed.png", "speed");
    textures.AddTexture("Res/beam.png", "beam");
    textures.AddTexture("Res/Asteroid.png", "asteroid");
    textures.AddTexture("Res/shadow.png", "asteroidShadow");

    textures.setAllSmooth(smoothTextures);
    textures["life"].setSmooth(0);
    textures["bullet"].setSmooth(0);
    textures["speed"].setSmooth(0);
    player.Setup(&textures);
    player.player.setPosition(camera.getSize().x / 2, camera.getSize().y / 2);
    enemy.Start(&textures, &player.player.getPosition());
    asteroids.Start(textures);
    powerUp.Start(textures);

    lifeIcon.setSize(Vector2f(50, 50));
    boostIcon.setSize(Vector2f(50, 50));
    lifeIcon.setOrigin(lifeIcon.getSize().x / 2, lifeIcon.getSize().y / 2);
    boostIcon.setOrigin(boostIcon.getSize().x / 2, boostIcon.getSize().y / 2);
    lifeIcon.setTexture(&textures["life"]);
    boostIcon.setTexture(&textures["speed"]);


    Vector2f allPos = Vector2f(camera.getSize().x / 10, camera.getSize().y / 10);

    for (int i = 0; i < c_playerMaxBullets; i++)
    {
        bulletRecharge[i].setSize(Vector2f(70, 70));
        bulletRecharge[i].setOrigin(Vector2f(bulletRecharge[i].getSize().x / 2, bulletRecharge[i].getSize().y / 2));
        bulletRecharge[i].setPosition(allPos.x * (0.5 + i * 0.7), allPos.y * 9.4);
        bulletRecharge[i].setTexture(&textures["bullet"]);

    }

    textManager.AddFont("Res/Uni_Sans_Heavy.otf", "Default");
    textManager.AddText("GG1");
    textManager.AddText("GG2");
    textManager.AddText("Esc");
    textManager.AddText("Esc2");
    textManager.AddText("Esc3");
    textManager.AddText("lives");
    textManager.AddText("kills");

    textManager.AddText("speedBoost");

    for (int i = 0; i < c_playerMaxBullets; i++)
    {
        comboAlpha[i] = 0;
        textManager.AddText("combo" + to_string(i));
        textManager.AddText("bullet" + to_string(i));
        textManager.SetupText("bullet" + to_string(i), 25, Color::White, textManager.getFont("Default"),
            bulletRecharge[i].getPosition(), "0.0", Text::Style::Regular);
        textManager["bullet" + to_string(i)].setOrigin(
            textManager["bullet" + to_string(i)].getLocalBounds().width / 2,
            textManager["bullet" + to_string(i)].getLocalBounds().height);

        textManager.SetupText("combo" + to_string(i), 40, Color::Transparent, textManager.getFont("Default"),
            Vector2f(0, 0), "Combo", Text::Style::Regular);
    }


    lifeIcon.setPosition(allPos.x * 0.3, allPos.y * 0.5);
    boostIcon.setPosition(allPos.x * 8.8, allPos.y * 9.5);


    

    textManager.SetupText("GG1", 120, Color::White, textManager.getFont("Default"),
        Vector2f(allPos.x * 5, allPos.y * 3), "GAME OVER!", Text::Style::Regular);
    textManager.SetupText("Esc", 90, Color::White, textManager.getFont("Default"),
        Vector2f(allPos.x * 5, allPos.y * 3), "Paused", Text::Style::Regular);
    textManager.SetupText("Esc2", 40, Color::White, textManager.getFont("Default"),
        Vector2f(allPos.x * 5, allPos.y * 5.0), "Press esc again to quit", Text::Style::Regular);
    textManager.SetupText("Esc3", 40, Color::White, textManager.getFont("Default"),
        Vector2f(allPos.x * 5, allPos.y * 5.8), "Press any other key to resume", Text::Style::Regular);
    textManager.SetupText("GG2", 30, Color::White, textManager.getFont("Default"),
        Vector2f(allPos.x * 5, allPos.y * 6), "Press esc to continue!", Text::Style::Regular);
    textManager.SetupText("lives", 30, Color::White, textManager.getFont("Default"),
        Vector2f(allPos.x * 0.7, allPos.y * 0.5), "x5", Text::Style::Regular);
    textManager.SetupText("kills", 30, Color::White, textManager.getFont("Default"),
        Vector2f(allPos.x * 9.9, allPos.y * 0.3), "Kills: 0", Text::Style::Regular);
    textManager.SetupText("speedBoost", 30, Color::White, textManager.getFont("Default"),
        Vector2f(allPos.x * 9.3, allPos.y * 9.4), "+0%", Text::Style::Regular);

    textManager["lives"].setOutlineColor(Color::Black);
    textManager["lives"].setOutlineThickness(2);
    textManager["kills"].setOutlineColor(Color::Black);
    textManager["kills"].setOutlineThickness(2);
    textManager["speedBoost"].setOutlineColor(Color::Black);
    textManager["speedBoost"].setOutlineThickness(2);
    textManager["GG1"].setOutlineColor(Color(0, 0, 0, 128));
    textManager["GG1"].setOutlineThickness(5);
    textManager["GG2"].setOutlineColor(Color(0, 0, 0, 128));
    textManager["GG2"].setOutlineThickness(5);
    textManager["Esc"].setOutlineColor(Color(0, 0, 0, 128));
    textManager["Esc"].setOutlineThickness(5);
    textManager["Esc2"].setOutlineColor(Color(0, 0, 0, 128));
    textManager["Esc2"].setOutlineThickness(5);
    textManager["Esc3"].setOutlineColor(Color(0, 0, 0, 128));
    textManager["Esc3"].setOutlineThickness(5);


    textManager.setOrigin("kills", TextManager::Right);
    kills = 0;

    BulletTrail.MaxParticles = 500;
    BulletTrail.reset();
    BulletTrail.loadSettings("Res/BulletTrail.png");

    EnemyHit.MaxParticles = 150;
    EnemyHit.reset();
    EnemyHit.loadSettings("Res/EnemyHit.png");

    EnemySpawn.MaxParticles = 100;
    EnemySpawn.reset();
    EnemySpawn.loadSettings("Res/EnemySpawn.png");

    EnemyTrail.MaxParticles = 500;
    EnemyTrail.reset();
    EnemyTrail.loadSettings("Res/EnemyTrail.png");

    PlayerHit.MaxParticles = 50;
    PlayerHit.reset();
    PlayerHit.loadSettings("Res/PlayerHit.png");

    PlayerTrail.MaxParticles = 100;
    PlayerTrail.reset();
    PlayerTrail.loadSettings("Res/PlayerTrail.png");

    PowerUpCollect.MaxParticles = 5;
    PowerUpCollect.reset();
    PowerUpCollect.loadSettings("Res/PowerUpCollect.png");

    BulletExplode.MaxParticles = 50;
    BulletExplode.reset();
    BulletExplode.loadSettings("Res/BulletExplode.png");

    powerUp.powerUp.setOutlineColor(Color(BGSwitchColors[BGswitchIndices[bg.onPulse]].r,
        BGSwitchColors[BGswitchIndices[bg.onPulse]].g,
        BGSwitchColors[BGswitchIndices[bg.onPulse]].b, 64));

    for (int i = 0; i < asteroids.asteroids.size(); i++)
    {
        asteroids.asteroids[i].shadow.setOutlineColor(Color(
            BGSwitchColors[BGswitchIndices[bg.onPulse]].r,
            BGSwitchColors[BGswitchIndices[bg.onPulse]].g,
            BGSwitchColors[BGswitchIndices[bg.onPulse]].b, 32));

    }

    Update();
}

bool App::Pause()
{
    while (window.isOpen())
    {
        Event event;
        InputEvent::OnceUpdate();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            InputEvent::EventUpdate(event);
        }
        if (InputEvent::isKeyReleased(Keyboard::Escape))
            break;
        for (int i = 0; i < Keyboard::KeyCount; i++)
        {
            if (i == Keyboard::Escape)
                continue;
            else
                if (InputEvent::isKeyReleased((Keyboard::Key)i))
                {
                    return 0;
                }
        }

        sleep(milliseconds(33));
        if (fpsMode)
            window.setTitle("FPS: " + to_string(int(1 / TimeManager::getDeltaTime().asSeconds())));
        TimeManager::Restart();
    }
    return 1;
}

void App::CheckHitBoxes()
{
    for (int i = 0; i < c_maxAsteroids; i++)
    {
        if (!asteroids.asteroids[i].active)
            continue;
        for (int j = 0; j < c_maxEnemies; j++)
        {
            if (!enemy.enemies[j].active)
                continue;
            if (Collision::Circle_Circle(asteroids.asteroids[i].shape.getPosition(),
                enemy.enemies[j].player.getPosition(), asteroids.asteroids[i].shape.getRadius(),
                c_enemyHitBoxSize))
            {
                EnemyHit.setPosition(enemy.enemies[j].player.getPosition());
                EnemyHit.createNew();
                enemy.enemies[j].Delete();
            }
        }
        for (int j = 0; j < player.usingBullets; j++)
        {
            if (!player.bullet[j].active)
                continue;
            if (Collision::Circle_Circle(asteroids.asteroids[i].shape, player.bullet[j].bullet))
            {
                BulletExplode.setPosition(player.bullet[j].bullet.getPosition());
                BulletExplode.createNew();
                player.bullet[j].Delete();
            }
        }
        if (Collision::Circle_Circle(asteroids.asteroids[i].shape.getPosition(),
            player.player.getPosition(), asteroids.asteroids[i].shape.getRadius(),
            c_userHitBoxSize))
        {
            camera.setShake(20, 0.5, 1);
            player.hp = 0;
            PlayerHit.setPosition(player.player.getPosition());
            PlayerHit.createNew();
            textManager["lives"].setString("x" + to_string(player.hp));
        }
    }
    for (int i = 0; i < c_maxEnemies; i++)
    {
        if (!enemy.enemies[i].active)
            continue;
        if (Collision::Circle_Circle(enemy.enemies[i].player.getPosition(),
            player.player.getPosition(), c_enemyHitBoxSize,
            c_userHitBoxSize))
        {
            camera.setShake(20, 0.5, 1);
            EnemyHit.setPosition(enemy.enemies[i].player.getPosition());
            EnemyHit.createNew();
            enemy.enemies[i].Delete();
            kills++;
            player.hp--;
            PlayerHit.setPosition(player.player.getPosition());
            PlayerHit.createNew();
            soundManager.reset("hit");
            textManager["lives"].setString("x" + to_string(player.hp));
            textManager["kills"].setString("Kills: " + to_string(kills));
            textManager.setOrigin("kills", TextManager::Right);
        }
    }
    //player bullet
    for (int j = 0; j < c_playerMaxBullets; j++)
    {
        if (player.bullet[j].bullet.getPosition().x < 0 || player.bullet[j].bullet.getPosition().y < 0 ||
            player.bullet[j].bullet.getPosition().x > camera.getSize().x || player.bullet[j].bullet.getPosition().y > camera.getSize().y)
        {
            player.bullet[j].active = 0;
        }
        if (player.bullet[j].active)
        {
            float distanceFromPlayer = Distance::Point_Point(player.bullet[j].bullet.getPosition(), player.player.getPosition());
            for (int i = 0; i < c_maxEnemies; i++)
            {
                if (player.bullet[j].active && player.bullet[j].beamTargetID == i &&
                    !enemy.enemies[i].active && player.bullet[j].hitCnt > 0)
                {
                    player.bullet[j].doNotDrawBeam = 1;
                }
                if (!enemy.enemies[i].active)
                    continue;
                if (Collision::Circle_Circle(enemy.enemies[i].player.getPosition(), player.bullet[j].bullet.getPosition(),
                    c_enemyHitBoxSize, player.bullet[j].bullet.getRadius()))
                {

                    if (player.bullet[j].hitCnt > 0)
                    {
                        comboAlpha[j] = 255;
                        textManager["combo" + to_string(j)].setCharacterSize(player.bullet[j].hitCnt + 15);
                        textManager["combo" + to_string(j)].setString("Combo x" + to_string(player.bullet[j].hitCnt + 1));
                        textManager["combo" + to_string(j)].setFillColor(Color(255, 255 - player.bullet[j].hitCnt * 2, 0, comboAlpha[j]));
                        textManager["combo" + to_string(j)].setPosition(player.bullet[j].bullet.getPosition());
                        int randRotation = rand() % 40 - 20;
                        int randAngle = rand() % 360;
                        textManager["combo" + to_string(j)].move(cos(randAngle * 0.0174533) * 20,
                            sin(randAngle * 0.0174533) * 20);
                        textManager["combo" + to_string(j)].setRotation(randRotation);
                    }


                    camera.setShake(15, 0.2, 1);

                    EnemyHit.setPosition(enemy.enemies[i].player.getPosition());
                    EnemyHit.createNew();
                    enemy.enemies[i].Delete();
                    soundManager.reset("ex" + to_string(rand() % 3 + 1));
                    kills++;
                    textManager["kills"].setString("Kills: " + to_string(kills));
                    textManager.setOrigin("kills", TextManager::Right);
                    float distance = 0;
                    bool drawBeam = 1;
                    unsigned int ID = enemy.FindClosestEnemy(player.bullet[j].bullet.getPosition(), distance);
                    if (distanceFromPlayer < distance && distanceFromPlayer > c_userHitBoxSize)
                    {
                        if (abs(player.acc.x) > 0.1 || abs(player.acc.y) > 0.1)
                        {
                            Vector2f pos = player.player.getPosition();
                            Vector2f dir = pos - player.bullet[j].bullet.getPosition();
                            player.bullet[j].Bounce(atan2(dir.y, dir.x) * 57.2958, &player.player.getPosition());
                            ID = -1;
                            player.bullet[j].beamTargetID = ID;
                            drawBeam = 0;
                        }
                    }
                    if (ID != -1)
                    {
                        Vector2f pos = enemy.enemies[ID].player.getPosition();
                        Vector2f dir = pos - player.bullet[j].bullet.getPosition();
                        player.bullet[j].beamTargetID = ID;
                        player.bullet[j].Bounce(atan2(dir.y, dir.x) * 57.2958, &enemy.enemies[ID].player.getPosition());
                        drawBeam = 0;
                    }
                    if (drawBeam)
                        player.bullet[j].doNotDrawBeam = drawBeam;
                }
            }
            //collision with player
            if (player.bullet[j].hitCnt > 0 && Collision::Circle_Circle(player.player.getPosition(), player.bullet[j].bullet.getPosition(),
                c_enemyHitBoxSize, player.bullet[j].bullet.getRadius()))
            {
                camera.setShake(20, 0.5, 1);

                player.hp--;
                PlayerHit.setPosition(player.player.getPosition());
                PlayerHit.createNew();
                soundManager.reset("hit");
                textManager["lives"].setString("x" + to_string(player.hp));
                BulletExplode.setPosition(player.bullet[j].bullet.getPosition());
                BulletExplode.createNew();
                player.bullet[j].Delete();
            }
        }
    }
    //powerup
    if (powerUp.active && Collision::Circle_Rectangle(player.player.getPosition(), c_userHitBoxSize, 
        FloatRect(powerUp.powerUp.getPosition().x - powerUp.powerUp.getSize().x / 2, powerUp.powerUp.getPosition().y - powerUp.powerUp.getSize().y / 2,
            powerUp.powerUp.getSize().x, powerUp.powerUp.getSize().y)))
    {
        PowerUpCollect.setPosition(powerUp.powerUp.getPosition());
        PowerUpCollect.createNew();
        powerUp.active = 0;
        switch (powerUp.ID)
        {
        case 0:
            player.hp += 2;
            textManager["lives"].setString("x" + to_string(player.hp));
            break;
        case 1:
            if (player.usingBullets < 10)
                player.usingBullets++;
            break;
        case 2:
            player.playerMaxSpeed += 0.2;
            textManager["speedBoost"].setString("+" + to_string(int((player.playerMaxSpeed - 1) * 100)) + "%");
            break;
        }
        soundManager.reset("powerup");
    }
    //enemy wander mode
    
    for (int j = 0; j < c_maxEnemies; j++)
    {
        if (!enemy.enemies[j].active)
            continue;
        bool collision = 0;
        for (int i = 0; i < c_maxAsteroids; i++)
        {
            if (!asteroids.asteroids[i].active)
                continue;
            if (Collision::Line_Circle(asteroids.asteroids[i].shape, enemy.enemies[j].player.getPosition(),
                player.player.getPosition()))
            {
                collision = 1;
                
                break;
            }

        }
        if (collision)
        {
            if (!enemy.enemies[j].wanderMode)
            {
                enemy.enemies[j].SetWanderLocation(camera.camera);
            }
        }
        else
        {
            enemy.enemies[j].wanderMode = 0;
        }
        if (enemy.enemies[j].wanderMode)
            for (int i = 0; i < c_maxAsteroids; i++)
            {
                if (!asteroids.asteroids[i].active)
                    continue;
                if (Collision::Line_Circle(asteroids.asteroids[i].shape, enemy.enemies[j].player.getPosition(),
                    enemy.enemies[j].wanderLocation))
                {
                    enemy.enemies[j].SetWanderLocation(camera.camera);
                }

            }
    }
}

void App::Update()
{
    while (window.isOpen())
    {
        Event event;
        InputEvent::OnceUpdate();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            InputEvent::EventUpdate(event);
        }
        camera.Update(window, TimeManager::getDeltaTime().asSeconds());

        if (player.hp <= 0 && !gameOver)
        {
            soundManager.reset("death");
            gameOver = 1;
        }
        bool changed = bg.Update();
        if (changed)
        {
            for (int i = 0; i < asteroids.asteroids.size(); i++)
            {
                asteroids.asteroids[i].shadow.setOutlineColor(Color(
                    BGSwitchColors[BGswitchIndices[bg.onPulse]].r,
                    BGSwitchColors[BGswitchIndices[bg.onPulse]].g,
                    BGSwitchColors[BGswitchIndices[bg.onPulse]].b, 32));
               
            }
            powerUp.powerUp.setOutlineColor(Color(BGSwitchColors[BGswitchIndices[bg.onPulse]].r,
                BGSwitchColors[BGswitchIndices[bg.onPulse]].g,
                BGSwitchColors[BGswitchIndices[bg.onPulse]].b, 64));
        }
        if (!gameOver)
        {
            CheckHitBoxes();
            player.Update(window, camera.camera);

            enemy.Update(window, camera.camera);

            asteroids.Update(camera.camera);
            powerUp.Update(camera.camera);

            //update particles
            BulletTrail.update(TimeManager::getDeltaTime().asSeconds() * 144);
            EnemyHit.update(TimeManager::getDeltaTime().asSeconds() * 144);
            EnemySpawn.update(TimeManager::getDeltaTime().asSeconds() * 30);
            EnemyTrail.update(TimeManager::getDeltaTime().asSeconds() * 144);
            PlayerHit.update(TimeManager::getDeltaTime().asSeconds() * 144);
            PlayerTrail.update(TimeManager::getDeltaTime().asSeconds() * 144);
            PowerUpCollect.update(TimeManager::getDeltaTime().asSeconds() * 144);
            BulletExplode.update(TimeManager::getDeltaTime().asSeconds() * 144);
            if (escMode)
            {
                if (Pause())
                    break;
                escMode = 0;
            }
            if (InputEvent::isKeyReleased(Keyboard::Escape) || !InputEvent::WindowHasFocus())
            {
                escMode = 1;
               
            }
        }
        else
        {
            if (InputEvent::isKeyReleased(Keyboard::Escape))
            {
                break;
            }
        }
        if (InputEvent::isKeyReleased(Keyboard::F3))
        {
            fpsMode = !fpsMode;
            if (!fpsMode)
                window.setTitle(AppName);
        }
        for (int i = 0; i < player.usingBullets; i++)
        {
            if (player.bullet[i].bulletRecharge > 0)
            {
                int alpha = (1 - player.bullet[i].bulletRecharge / c_playerBulletRecharge) * 96;
                bulletRecharge[i].setFillColor(Color(255, 255, 255, alpha));
                textManager["bullet" + to_string(i)].setString(to_string(int(player.bullet[i].bulletRecharge)) +
                    "." + to_string(int((player.bullet[i].bulletRecharge - int(player.bullet[i].bulletRecharge)) * 10)));
            }
            else
            {
                bulletRecharge[i].setFillColor(Color(255, 255, 255, 255));
            }
            if (comboAlpha[i] > 0)
            {
                comboAlpha[i] -= TimeManager::getDeltaTime().asSeconds() * 100;
                textManager["combo" + to_string(i)].setFillColor(Color(
                    textManager["combo" + to_string(i)].getFillColor().r,
                    textManager["combo" + to_string(i)].getFillColor().g,
                    textManager["combo" + to_string(i)].getFillColor().b,
                    comboAlpha[i]));
            }
        }
        window.clear();
        window.draw(bg);
        window.draw(powerUp);
        //draw particles
        window.draw(BulletTrail);
        window.draw(EnemyHit);
        window.draw(EnemySpawn);
        window.draw(EnemyTrail);
        window.draw(PlayerHit);
        window.draw(PlayerTrail);
        window.draw(PowerUpCollect);
        window.draw(BulletExplode);

        for (int i = 0; i < player.usingBullets; i++)
            if (!player.bullet[i].doNotDrawBeam && player.bullet[i].active && player.bullet[i].hitCnt > 0)
            {
                window.draw(player.bullet[i].beam);
            }
        window.draw(enemy);
        for (int i = 0; i < player.usingBullets; i++)
            window.draw(player.bullet[i]);
        if (player.hp > 0)
            window.draw(player);
        window.draw(asteroids);
        //UI
        window.draw(boostIcon);
        window.draw(lifeIcon);
        for (int i = 0; i < player.usingBullets; i++)
        {
            window.draw(bulletRecharge[i]);
            if (player.bullet[i].bulletRecharge > 0)
                window.draw(textManager["bullet" + to_string(i)]);
            if (comboAlpha[i] > 0)
                window.draw(textManager["combo" + to_string(i)]);
        }
        window.draw(textManager["lives"]);
        window.draw(textManager["kills"]);
        window.draw(textManager["speedBoost"]);
        if (escMode)
        {
            window.draw(textManager["Esc"]);
            window.draw(textManager["Esc2"]);
            window.draw(textManager["Esc3"]);
        }
        if (gameOver)
        {
            window.draw(textManager["GG1"]);
            window.draw(textManager["GG2"]);
            moveEndScreen += TimeManager::getDeltaTime().asSeconds() * 300;
            textManager.getText("GG2").move(0, sin(moveEndScreen * 0.0174533) * 14.4 * TimeManager::getDeltaTime().asSeconds());
        }
        //window.draw(textManager.getText("GG1"));
        //window.draw(textManager.getText("GG2"));
        window.display();
        if (fpsMode)
            window.setTitle("FPS: " + to_string(int(1 / TimeManager::getDeltaTime().asSeconds())));
        TimeManager::Restart();
    }
}
