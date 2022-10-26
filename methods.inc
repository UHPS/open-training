CB:setHealth(const playerid, const blockid, const world, const argumentIdx) {
    new arguments[TEXT_FUNCTION_ARGUMENT],
        Float: health;

    ReadAmxMemoryArray(argumentIdx, arguments); // Получаем аргументы по индексу

    if (sscanf(arguments, "f", health)) {
        return SendMissCBMessage(playerid, blockid, "health"); // [CB:%d player:%d]: Не указано значение: weapon, ammo
    }

    if (!cmBlock[world][blockid][cbMode]) { // Если активация блока не на группу игроков
        SetPlayerHealth(playerid, health);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) { // Проверка игрока на сооветсвтие условиеям блока.
            continue;
        }

        SetPlayerHealth(targetid, hp);
    }

    return true;
}

CB:giveWeapon(const playerid, const blockid, const world, const argumentIdx) {
    new weapon,
        ammo,
        arguments[TEXT_FUNCTION_ARGUMENT],
        Float: health;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(params, "dd", weapon, ammo)) {
        return SendMissCBMessage(playerid, blockid, "weapon, ammo"); // [CB:%d player:%d]: Не указано значение: weapon, ammo
    }

    if (0 > weapon > 46) {
        return SendErrorCBMessage(playerid, blockid, "weapon", "0-46"); // [CB:%d player:%d weapon:%d]: weapon не соотвествует условию: <0-46>
    }

    if (!cmBlock[world][blockid][cbMode]) {
        GiveGun(playerid, weapon, ammo);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        GiveGun(targetid, weapon, ammo);
    }

    return true;
}