CB:setHealth(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new arguments[TEXT_FUNCTION_ARGUMENT],
        Float: health;

    ReadAmxMemoryArray(argumentIdx, arguments); // Получаем аргументы по индексу

    if (sscanf(arguments, "f", health)) {
        return SendMissCBMessage(playerid, blockid, actionid, "health"); // [CB:%d/%d player:%d]: Не указано значение: weapon, ammo
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

CB:addHealth(const playerid, const blockid, const actionid, const world, const argumentIdx)
{
	new Float: hp,
        arguments[TEXT_FUNCTION_ARGUMENT];
        
    ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "f", hp))
		return SendMissCBMessage(playerid, blockid, actionid, "health");

    if (!cmBlock[world][blockid][cbMode]) { 
        SetPlayerHealth(playerid, pData[playerid][pHealth] + hp);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) 
        {
            continue;
        }

        SetPlayerHealth(targetid, pData[targetid][pHealth] + hp);
    }
	return true;
}

CB:setArmor(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new arguments[TEXT_FUNCTION_ARGUMENT],
        Float: armour;

    ReadAmxMemoryArray(argumentIdx, arguments); 

    if (sscanf(arguments, "f", armour)) {
        return SendMissCBMessage(playerid, blockid, actionid, "armour");
    }

    if (!cmBlock[world][blockid][cbMode]) { //
        SetPlayerArmour(playerid, armour);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) { 
            continue;
        }

        SetPlayerArmour(targetid, armour);
    }

    return true;
}

CB:addArmor(const playerid, const blockid, const actionid, const world, const argumentIdx)
{
	new Float: arm,
        arguments[TEXT_FUNCTION_ARGUMENT];
        
    ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "f", arm))
		return SendMissCBMessage(playerid, blockid, actionid, "armour");

    if (!cmBlock[world][blockid][cbMode]) { 
        SetPlayerHealth(playerid, pData[playerid][pArmour] + arm);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) 
        {
            continue;
        }

        SetPlayerHealth(targetid, pData[targetid][pArmour] + arm);
    }
	return true;
}

CB:setPos(const playerid, const blockid, const actionid, const world, const argumentIdx)
{
	new Float: x,
        Float: y,
        Float: z,
        arguments[TEXT_FUNCTION_ARGUMENT];
        
    ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "fff", x, y, z))
		return SendMissCBMessage(playerid, blockid, actionid, "x y z");

    if (!cmBlock[world][blockid][cbMode]) { 
        SetPlayerPos(playerid, x, y, z);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) 
        {
            continue;
        }

        SetPlayerPos(targetid, x, y, z);
    }
	return true;
}

CB:setSkin(const playerid, const blockid, const actionid, const world, const argumentIdx)
{
	new skin,
        arguments[TEXT_FUNCTION_ARGUMENT];
        
    ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "d", skin))
		return SendMissCBMessage(playerid, blockid, actionid, "skin");
       
    if(0 > skin > 311)
        return SendErrorCBMessage(playerid, blockid, actionid, "skin", "0-311"); 

    if (!cmBlock[world][blockid][cbMode]) { 
        SetPlayerSkin(playerid, skin);
        pData[playerid][pSkin] = skin;
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) 
        {
            continue;
        }

        SetPlayerSkin(targetid, skin);
        pData[targetid][pSkin] = skin;
    }
	return true;
}

CB:setTime(const playerid, const blockid, const actionid, const world, const argumentIdx)
{
	new time,
        arguments[TEXT_FUNCTION_ARGUMENT];
        
    ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "d", time))
		return SendMissCBMessage(playerid, blockid, actionid, "time");
       
    if(0 > time > 24)
        return SendErrorCBMessage(playerid, blockid, actionid, "time", "0-24"); 

    if (!cmBlock[world][blockid][cbMode]) { 
        SetPlayerTime(playerid, time, 0);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerTime(targetid, time, 0);

    }
	return true;
}

CB:setWeather(const playerid, const blockid, const actionid, const world, const argumentIdx)
{
	new weather,
        arguments[TEXT_FUNCTION_ARGUMENT];
        
    ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "d", weather))
		return SendMissCBMessage(playerid, blockid, actionid, "weather");
       
    if(0 > weather > 255)
        return SendErrorCBMessage(playerid, blockid, actionid, "weather", "0-255"); 

    if (!cmBlock[world][blockid][cbMode]) { 
        SetPlayerWeather(playerid, weather);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerWeather(targetid, weather);

    }
	return true;
}

CB:giveWeapon(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new weapon,
        ammo,
        arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dd", weapon, ammo)) {
        return SendMissCBMessage(playerid, blockid, actionid, "weapon, ammo"); // [CB:%d/%d player:%d]: Не указано значение: weapon, ammo
    }

    if (0 > weapon > 46) {
        return SendErrorCBMessage(playerid, blockid, actionid, "weapon", "0-46"); // [CB:%d/%d player:%d weapon:%d]: weapon не соотвествует условию: <0-46>
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

CB:resetWeapom(const playerid, const blockid, const actionid, const world, const argumentIdx)
{

    if (!cmBlock[world][blockid][cbMode]) { 
        ResetGun(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        ResetGun(targetid);

    }
	return true;
}

CB:giveMoney(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new money,
        arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", money)) {
        return SendMissCBMessage(playerid, blockid, actionid, "money");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        AddPlayerMoney(playerid, money);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        AddPlayerMoney(targetid, money);
    }

    return true;
}

CB:resetMoney(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {
        ResetPlayerMoney(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        ResetPlayerMoney(targetid);
    }

    return true;
}

CB:setSpawn(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {
        SpawnPlayer(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SpawnPlayer(targetid);
    }

    return true;
}

CB:sendMessage(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new str[144],
        arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "s[144]", str)) {
        return SendMissCBMessage(playerid, blockid, actionid, "string");
    }
    
    if(VW[world][vDev])
		format(str, sizeof(str), "[CB:%d]: {FFFFFF}%s", blockid, str);
	else
		format(str, sizeof(str), "[CB]: {FFFFFF}%s", str);
        

    if (!cmBlock[world][blockid][cbMode]) {
        SendClientMessage(playerid, COLOR_ORANGE, str);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SendClientMessage(targetid, COLOR_ORANGE, str);
    }

    return true;
}
