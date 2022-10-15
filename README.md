    resolveTargetOrSelf(playerid, argumentIdx) - Возвращает указанного игрока или инициатора форматируя его за вас.
    Пример:
        #money(10)# -> resolveTargetOrSelf(playerid, argumentIdx) -> targetid = 10
        #money# -> resolveTargetOrSelf(playerid, argumentIdx) -> targetid = playerid
    * Обратите внимания на функцию CBF:money там нет sscanf потому что эта функция сама форматирует это.
    ** Это сделано для того что не дублировать код где проверяется есть ли указанный id или нет.


    getTargetIdOrSelf(playerid, targetid) - Возвращает указанного игрока или инициатора.
    Пример:
        if (sscanf(arg, "dD(-1)", targetid, weaponSlot)) {
            targetid = playerid;
        } else {
            targetid = getTargetIdOrSelf(playerid, targetid);
        }
    * Почти тоже самое что и выше, но необходимо для случаев где есть необязательные параметры или первый вариант не подходит.

    ReadAmxMemoryArray(argumentIdx, arguments) - функция которая получает переменную по индексу, особенность сампа.
    WriteAmxMemoryArray(resultIdx, value) - записываем строку с результатом по индексу переменной, так же особенность сампа.
