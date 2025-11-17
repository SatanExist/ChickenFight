  ##  GAS: Драка на арене
  
Этот репозиторий содержит C++ и Blueprint логику для системы боя, реализованную по паттерну GAS.

* **Unreal Engine Version:** 5.5 
* **IDE:** Visual Studio 2022 (с установленной рабочей нагрузкой "Game development with C++").

* Проект требует активации следующих официальных плагинов:
    1) GameplayAbility


  ##  Пошаговый Запуск

Поскольку это C++ проект, он не может быть запущен напрямую. Необходимо сгенерировать файлы решения.

1.  **Клонирование Репозитория:**
    ```bash
    git clone https://github.com/SatanExist/ChickenFight.git
    ```
2.  **Генерация Файлов Visual Studio (.sln):**
    * В папке проекта найдите файл `ChickenFight.uproject`.
    * **Правой кнопкой мыши** -> **Generate Visual Studio project files**.
3.  **Сборка C++:**
    * Откройте сгенерированный файл `MVVM.sln` в Visual Studio.
    * Установите конфигурацию: **`Development Editor`** | **`Win64`**.
    * Соберите решение: **`Build`** -> **`Build Solution`**.
4.  **Запуск:** После успешной сборки откройте проект двойным кликом по файлу `ChickenFight.uproject`.

  ## Movement

  1. WASD - перемещение
  2. Цифра 1 - взять/убрать оружие в руках.
  3. Shift - Рывок.
  4. Пробел - удар оружием.
