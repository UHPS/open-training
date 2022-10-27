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

CB:playSound(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new sound,
    	Float: x,
	Float: y,
	Float: z,
        arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dF(0)F(0)F(0)", sound, x, y, z)) {
        return SendMissCBMessage(playerid, blockid, actionid, "sound [x y z]");
    }

    if (0 > weapon > 65535) {
        return SendErrorCBMessage(playerid, blockid, actionid, "sound", "0-65535");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        PlayerPlaySound(playerid, sound, x, y, z);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        PlayerPlaySound(targetid, sound, x, y, z);
    }

    return true;
}

CB:setInterior(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new interior,
        arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", interior)) {
        return SendMissCBMessage(playerid, blockid, actionid, "interior");
    }

    if (0 > interior > 99) {
        return SendErrorCBMessage(playerid, blockid, actionid, "interior", "0-99");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerInterior(playerid, sound, x, y, z);

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerInterior(targetid, sound, x, y, z);
    }

    return true;
}

CB:setChannel(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new channel,
        arguments[TEXT_FUNCTION_ARGUMENT];

        ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", channel)) {
        return SendMissCBMessage(playerid, blockid, actionid, "channel");
    }

    if (0 > channel > 999) {
        return SendErrorCBMessage(playerid, blockid, actionid, "channel", "0-999"); 
    }

    if(!cmBlock[world][blockid][cbMode]) {
        pData[playerid][pChannel] = channel;

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        pData[targetid][pChannel] = channel;
    }
    return true;
}

CB:setTeam(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new team,
        arguments[TEXT_FUNCTION_ARGUMENT];

        ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", team)) {
        return SendMissCBMessage(playerid, blockid, actionid, "team");
    }

    if (0 > team > MAX_WORLD_TEAM) {
        return SendErrorCBMessage(playerid, blockid, actionid, "team", "0-999"); 
    }

    teamid--;

    if(!cmBlock[world][blockid][cbMode]) {
        pData[playerid][pTeam] = teamid;

        if(teamid != -1) {
            if(worldTeam[world][teamid][tSkin]) {
			    pData[playerid][pSkin] = worldTeam[world][teamid][tSkin];
            }
        }

        SpawnZone(playerid);
	    SpawnPlayer(playerid);

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        pData[targetid][pTeam] = teamid;

         if(teamid != -1) {
            if(worldTeam[world][teamid][tSkin]) {
			    pData[targetid][pSkin] = worldTeam[world][teamid][tSkin];
            }
        }

        SpawnZone(targetid);
	    SpawnPlayer(targetid);
    }
    return true;
}

CB:setAnim(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new lib[16],
        anim[32],
        loop,
        freeze,
        arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "s[16]s[32]ll", lib, anim, loop, freeze)) {
        return SendMissCBMessage(playerid, blockid, actionid, "lib anim loop freeze");
    }

    if(!cmBlock[world][blockid][cbMode]) {
        if(freeze)
			ApplyAnimationEx(playerid, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);
		else
			ApplyAnimation(playerid, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if(freeze)
			ApplyAnimationEx(targetid, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);
		else
			ApplyAnimation(targetid, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);

    }
    return true;
}

CB:giveVehicle(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new interior,
        model[32],
        Float: playerPos[4],
        color1,
        color2,
        siren,
        vehicleid;
        arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "s[32]I(-1)I(-1)D(0)", model, color1, color2, siren)) {
        return SendMissCBMessage(playerid, blockid, actionid, "model [color1 color2 siren]");
    }

    if(!cmBlock[world][blockid][cbMode]) {

        if(IsPlayerInAnyVehicle(playerid)) {
            return true;
        }

        GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
        GetPlayerFacingAngle(playerid, playerPos[3]);
        interior = GetPlayerInterior(playerid);

        vehicleid = CreateVehicleEx(model[0], playerPos, color1, color2, world, interior, siren);

        if(vehicleid == -1)
		{
				return SendMissCBMessage(playerid, blockid, actionid, "Достигнут лимит транспорта!");
		}

        pData[playerid][pRetVal][0] = vehicleid;

        vData[ tempWorld[world][vehSlot][vehicleid] ][vOwner] = pData[playerid][pID];
		vData[ tempWorld[world][vehSlot][vehicleid] ][vTeam] = -1;

        PutPlayerVeh(playerid, tempWorld[world][vehSlot][vehicleid], 0);

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }


        GetPlayerPos(targetid, playerPos[0], playerPos[1], playerPos[2]);
        GetPlayerFacingAngle(targetid, playerPos[3]);
        interior = GetPlayerInterior(targetid);

        vehicleid = CreateVehicleEx(model[0], playerPos, color1, color2, world, interior, siren);

        if(vehicleid == -1)
	{
		return SendMissCBMessage(targetid, blockid, actionid, "Достигнут лимит транспорта!");
	}

        pData[targetid][pRetVal][0] = vehicleid;

        vData[ tempWorld[world][vehSlot][vehicleid] ][vOwner] = pData[targetid][pID];
		vData[ tempWorld[world][vehSlot][vehicleid] ][vTeam] = -1;

        PutPlayerVeh(targetid, tempWorld[world][vehSlot][vehicleid], 0);

    }
    return true;
}

