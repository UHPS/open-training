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
            return false;
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

        if(IsPlayerInAnyVehicle(targetid)) {
          return false;
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

CB:setVehHP(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: health,
        arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "f", health)) {
        return SendMissCBMessage(playerid, blockid, actionid, "health");
    }

   if (0 > health > 9999) {
        return SendErrorCBMessage(playerid, blockid, actionid, "health", "0-9999"); 
    }

    if(!cmBlock[world][blockid][cbMode]) {

			  if(!IsPlayerInAnyVehicle(playerid))
				    continue;

			  SetVehicleHealth(GetPlayerVehicleID(playerid), health);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

  			if(!IsPlayerInAnyVehicle(targetid)) {
				  continue;
        }

			  SetVehicleHealth(GetPlayerVehicleID(targetid), health);
        return true;
    }
    return true;
}

CB:addVehHP(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new Float: health,
      Float: oldhealth,
      arguments[TEXT_FUNCTION_ARGUMENT];

 ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "f", health)) {
    return SendMissCBMessage(playerid, blockid, actionid, "health");
  }

  if (0 > health > 9999) {
    return SendErrorCBMessage(playerid, blockid, actionid, "health", "0-9999"); 
  }

  if(!cmBlock[world][blockid][cbMode]) {

    if(!IsPlayerInAnyVehicle(playerid))
        continue;
    GetVehicleHealth(GetPlayerVehicleID(playerid), oldhealth);
    SetVehicleHealth(GetPlayerVehicleID(playerid), oldhealth + health);
    return true;
  }

  foreach(new targetid : Player) {
    if (!cbCompareMode(targetid, blockid, world)) {
        continue;
    }

    if(!IsPlayerInAnyVehicle(targetid)) {
      continue;
    }

    GetVehicleHealth(GetPlayerVehicleID(targetid), oldhealth);
    SetVehicleHealth(GetPlayerVehicleID(targetid), oldhealth + health);
  }
  return true;
}

CB:SetVehData(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new vehicleid,
        slot,
        value,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "ddd", vehicleid, slot, value)) {
    return SendMissCBMessage(playerid, blockid, actionid, "vehicleid slot value");
  }

  if (0 > slot > 49) { 
    return SendErrorCBMessage(playerid, blockid, actionid, "slot", "0-49");
  }

  if (0 > vehicleid > MAX_VEHICLES) {
    return SendMissCBMessage(playerid, blockid, actionid, "vehicleid");
  }

  if (vehicleid != 0) {
    if(GetVehicleVirtualWorld(vehicleid) != world) {
      return false;
    }
    vData[vehicleid][vArray][slot] = value;
    return true;
  }

  if(!cmBlock[world][blockid][cbMode]) {
    if(!IsPlayerInAnyVehicle(playerid)) {
      return false;
    }
    vehicleid = GetPlayerVehicleID(playerid);
    vData[vehicleid][vArray][slot] = value;
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(!IsPlayerInAnyVehicle(targetid)) {
			continue;
    }

    vehicleid = GetPlayerVehicleID(targetid);
    vData[vehicleid][vArray][slot] = value;
  }

   return true;
}

CB:AddVehData(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new vehicleid,
        slot,
        value,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "ddd", vehicleid, slot, value)) {
    return SendMissCBMessage(playerid, blockid, actionid, "vehicleid slot value");
  }

  if (0 > slot > 49) { 
    return SendErrorCBMessage(playerid, blockid, actionid, "slot", "0-49");
  }

  if (0 > vehicleid > MAX_VEHICLES) {
    return SendMissCBMessage(playerid, blockid, actionid, "vehicleid");
  }

  if(GetVehicleVirtualWorld(vehicleid) != world) {
		return false
  }

  if (vehicleid != 0) {
    if(GetVehicleVirtualWorld(vehicleid) != world) {
      return false;
    }
    vData[vehicleid][vArray][slot] += value;
    return true;
  }

  if(!cmBlock[world][blockid][cbMode]) {
    if(!IsPlayerInAnyVehicle(playerid)) {
      return false;
    }
    vehicleid = GetPlayerVehicleID(playerid);
    vData[vehicleid][vArray][slot] += value;
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(!IsPlayerInAnyVehicle(targetid)) {
			continue;
    }
    
    vehicleid = GetPlayerVehicleID(targetid);
    vData[vehicleid][vArray][slot] += value;
  }

   return true;
}


CB:spawnVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {

  if(!cmBlock[world][blockid][cbMode]) {
    if(!IsPlayerInAnyVehicle(playerid)) {
      return false;
    }
    SetVehicleToRespawn(GetPlayerVehicleID(playerid));
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(!IsPlayerInAnyVehicle(targetid)) {
			continue;
    }
    
    SetVehicleToRespawn(GetPlayerVehicleID(targetid));
  }

   return true;
}

CB:sprayVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   color1,
        color2,
        vehicleid,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "ddD(0)", color1, color2, vehicleid)) {
    return SendMissCBMessage(playerid, blockid, actionid, "color1 color2 [vehicleid]");
  }

  if(vehicleid != 0) {
    if (0 > vehicleid > MAX_VEHICLES) {
      return false;
    }

    if(GetVehicleVirtualWorld(vehicleid) != world) {
		  return false;
    }   

    ChangeVehicleColor(vehicleid, color1, color2);
  }

  if(!cmBlock[world][blockid][cbMode]) {
    if(!IsPlayerInAnyVehicle(playerid)) {
      return false;
    }
    
    ChangeVehicleColor(GetPlayerVehicleID(playerid), color1, color2);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(!IsPlayerInAnyVehicle(targetid)) {
			continue;
    }
    
    ChangeVehicleColor(GetPlayerVehicleID(targetid), color1, color2);
  }

   return true;
}

CB:addVehComp(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   vehComp,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", vehComp)) {
    return SendMissCBMessage(playerid, blockid, actionid, "vehicleComponent");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    if(!IsPlayerInAnyVehicle(playerid)) {
      return false;
    }
    
    AddVehicleComponent(GetPlayerVehicleID(playerid), vehComp);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(!IsPlayerInAnyVehicle(targetid)) {
			continue;
    }
    
    AddVehicleComponent(GetPlayerVehicleID(targetid), vehComp);
  }

   return true;
}

CB:delVehComp(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   vehComp,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", vehComp)) {
    return SendMissCBMessage(playerid, blockid, actionid, "vehicleComponent");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    if(!IsPlayerInAnyVehicle(playerid)) {
      return false;
    }
    
    RemoveVehicleComponent(GetPlayerVehicleID(playerid), vehComp);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(!IsPlayerInAnyVehicle(targetid)) {
			continue;
    }
    
    RemoveVehicleComponent(GetPlayerVehicleID(targetid), vehComp);
  }

   return true;
}

CB:delVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   vehicleid,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", vehicleid)) {
    return SendMissCBMessage(playerid, blockid, actionid, "vehicleID");
  }

  if (vehicleid > 0) {
    if (1 > vehicleid > MAX_VEHICLES) {
      return false;
    }

    if(GetVehicleVirtualWorld(vehicleid) != world) {
      return false;
    }

    DestroyVehicleEx(vehicleid, world);
    return true;
  }

  if(!cmBlock[world][blockid][cbMode]) {
    if(!IsPlayerInAnyVehicle(playerid)) {
      return false;
    }
    
    DestroyVehicleEx(GetPlayerVehicleID(playerid), vehComp);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(!IsPlayerInAnyVehicle(targetid)) {
			continue;
    }
    
    DestroyVehicleEx(GetPlayerVehicleID(targetid), vehComp);
  }

   return true;
}

CB:fixVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   vehicleid,
        Float: health,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "D(0)", vehicleid)) {
    return SendMissCBMessage(playerid, blockid, actionid, "vehicleID");
  }

  if (vehicleid > 0) {
    if (1 > vehicleid > MAX_VEHICLES) {
      return false;
    }

    if(GetVehicleVirtualWorld(vehicleid) != world) {
      return false;
    }

    GetVehicleHealth(vehicleid, health);

    RepairVehicle(vehicleid);
    SetVehicleHealth(vehicleid, health);
    return true;
  }

  if(!cmBlock[world][blockid][cbMode]) {
    if(!IsPlayerInAnyVehicle(playerid)) {
      return false;
    }
    
    GetVehicleHealth(GetPlayerVehicleID(playerid), health);

    RepairVehicle(GetPlayerVehicleID(playerid));
    SetVehicleHealth(GetPlayerVehicleID(playerid), health);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(!IsPlayerInAnyVehicle(targetid)) {
			continue;
    }
    
    GetVehicleHealth(GetPlayerVehicleID(targetid), health);

    RepairVehicle(GetPlayerVehicleID(targetid));
    SetVehicleHealth(GetPlayerVehicleID(targetid), health);
  }

   return true;
}

CB:setScore(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   score,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", score)) {
    return SendMissCBMessage(playerid, blockid, actionid, "score");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerScore(playerid, score);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerScore(targetid, score);
  }

   return true;
}

CB:addScore(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   score,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", score)) {
    return SendMissCBMessage(playerid, blockid, actionid, "score");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerScore(playerid, GetPlayerScore(playerid) + score);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerScore(targetid, GetPlayerScore(targetid) + score);
  }

   return true;
}

CB:setWanted(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   level,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", level)) {
    return SendMissCBMessage(playerid, blockid, actionid, "level");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerWantedLevel(playerid, level);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerWantedLevel(targetid, level);
  }

   return true;
}

CB:addWanted(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   level,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", level)) {
    return SendMissCBMessage(playerid, blockid, actionid, "level");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + level);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerWantedLevel(targetid, GetPlayerWantedLevel(targetid) + level);
  }

   return true;
}

CB:SetPlayerCP(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   Float: x,
        Float: y,
        Float: z,
        Float: size,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "ffff", x, y, z, size)) {
    return SendMissCBMessage(playerid, blockid, actionid, "x y z size");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerCheckpoint(playerid, x, y, z, size);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerCheckpoint(targetid, x, y, z, size);
  }

   return true;
}

CB:DisablePlayerCP(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  if(!cmBlock[world][blockid][cbMode]) {
    DisablePlayerCheckpoint(playerid);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	DisablePlayerCheckpoint(targetid);
  }

   return true;
}

CB:SetPlayerRaceCP(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   Float: x,
        Float: y,
        Float: z,
        Float: nx,
        Float: ny,
        Float: nz,
        Float: size,
        type,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dfffffff", type, x, y, z, nx, ny, nz, size)) {
    return SendMissCBMessage(playerid, blockid, actionid, "type x1 y1 z1 x2 y2 z2 size");
  }

  if(0 > type > 8) {
    return SendErrorCBMessage(playerid, blockid, actionid, "type", "0-8"); 
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerRaceCheckpoint(playerid, type, x, y, z, nx, ny, nz, size);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerRaceCheckpoint(targetid, type, x, y, z, nx, ny, nz, size);
  }

   return true;
}

CB:DisablePlayerRaceCP(const playerid, const blockid, const actionid, const world, const argumentIdx) {

  if(!cmBlock[world][blockid][cbMode]) {
    DisablePlayerRaceCheckpoint(playerid);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	DisablePlayerRaceCheckpoint(targetid);
  }

   return true;
}

CB:SetPlayerMapIcon(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   iconid,
        x,
        y,
        z,
        markertype,
        color,
        style,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dfffdxd", iconid, x, y, z, markertype, color, style)) {
    return SendMissCBMessage(playerid, blockid, actionid, "iconid x y z markertype color style");
  }

  if(0 > iconid > 99) {
    return SendErrorCBMessage(playerid, blockid, actionid, "iconid", "0-99"); 
  }

  if(0 > markertype > 63) {
    return SendErrorCBMessage(playerid, blockid, actionid, "markertype", "0-63"); 
  }

  if(0 > style > 4) {
    return SendErrorCBMessage(playerid, blockid, actionid, "style", "0-4"); 
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerMapIcon(playerid, iconid, x, y, z, markertype, color, style);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerMapIcon(targetid, iconid, x, y, z, markertype, color, style);
  }

   return true;
}

CB:RemovePlayerMapIcon(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   iconid,

        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", iconid)) {
    return SendMissCBMessage(playerid, blockid, actionid, "iconid");
  }

  if(0 > iconid > 99) {
    return SendErrorCBMessage(playerid, blockid, actionid, "iconid", "0-99"); 
  }

  if(!cmBlock[world][blockid][cbMode]) {
    RemovePlayerMapIcon(playerid, iconid);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	RemovePlayerMapIcon(targetid, iconid);
  }

   return true;
}

CB:SetPlayerAttach(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   iconid,

        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", slotid)) {
    return SendMissCBMessage(playerid, blockid, actionid, "slotid");
  }

  slotid--;
  if(0 > slotid > 9) {
    return SendErrorCBMessage(playerid, blockid, actionid, "slotid", "1-10"); 
  }

  if(!cmBlock[world][blockid][cbMode]) {
    if(sscanf(arguments,"p< >ddddfffffffff",
				slotid,
				pAttach[targetid][slotid][0],
				pAttach[targetid][slotid][1],
				pAttach[targetid][slotid][2],

				fpAttach[targetid][slotid][0],
				fpAttach[targetid][slotid][1],
				fpAttach[targetid][slotid][2],
				fpAttach[targetid][slotid][3],
				fpAttach[targetid][slotid][4],
				fpAttach[targetid][slotid][5],
				fpAttach[targetid][slotid][6],
				fpAttach[targetid][slotid][7],
				fpAttach[targetid][slotid][8]
			) ) return false;

  	SetPlayerAttach(playerid);
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

    if(sscanf(arguments,"p< >ddddfffffffff",
				slotid,
				pAttach[targetid][slotid][0],
				pAttach[targetid][slotid][1],
				pAttach[targetid][slotid][2],

				fpAttach[targetid][slotid][0],
				fpAttach[targetid][slotid][1],
				fpAttach[targetid][slotid][2],
				fpAttach[targetid][slotid][3],
				fpAttach[targetid][slotid][4],
				fpAttach[targetid][slotid][5],
				fpAttach[targetid][slotid][6],
				fpAttach[targetid][slotid][7],
				fpAttach[targetid][slotid][8]
			) ) break;

  	SetPlayerAttach(targetid);
  }

   return true;
}

CB:DelPlayerAttach(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   slotid,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", slotid)) {
    return SendMissCBMessage(playerid, blockid, actionid, "slotid");
  }

  slotid--;
  if (0 > slot > 9) {
    return SendErrorCBMessage(playerid, blockid, actionId, "slotid", "1-10")
  }

  if(!cmBlock[world][blockid][cbMode]) {

      if(slotid == 0)
			{
				for(new t; t < 10; t++)
				{
					pAttach[playerid][t][0] = false;
					pAttach[playerid][t][1] = false;
					RemovePlayerAttachedObject(playerid, t);
				}
        return true;
			}

				pAttach[playerid][slotid][0] = false;
				pAttach[playerid][slotid][1] = false;
				RemovePlayerAttachedObject(playerid, slotid);

    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	if(slotid == 0)
			{
				for(new t; t < 10; t++)
				{
					pAttach[targetid][t][0] = false;
					pAttach[targetid][t][1] = false;
					RemovePlayerAttachedObject(targetid, t);
				}
			}
			else
			{
				pAttach[targetid][slotid][0] = false;
				pAttach[targetid][slotid][1] = false;
				RemovePlayerAttachedObject(targetid, slotid);
			}
  }

   return true;
}

CB:ActivateGate(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   gateSlot,
        type,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dd", gateSlot, type)) {
    return SendMissCBMessage(playerid, blockid, actionid, "gateSlot type");
  }

  gateSlot--;
  if (0 > gateSlot > MAX_WORLD_GATES) {
    return SendErrorCBMessage(playerid, blockid, actionid, "gateSlot", "1-30")
  }

  if (0 > type > 3) {
    return SendErrorCBMessage(playerid, blockid, actionid, "type", "0-3")
  }

  if (!IsValideGate(world, gateSlot)) {
    return false;
  }

  if(type == 0)
	{
		worldGate[world][gateSlot][gStatus] = !worldGate[world][gateSlot][gStatus];

		if(worldGate[world][gateSlot][gStatus])
			MoveDynamicObject(worldGate[world][gateSlot][gID], worldGate[world][gateSlot][gPosEndX], worldGate[world][gateSlot][gPosEndY], worldGate[world][gateSlot][gPosEndZ], worldGate[world][gateSlot][gSpeed], worldGate[world][gateSlot][gPosEndRX], worldGate[world][gateSlot][gPosEndRY], worldGate[world][gateSlot][gPosEndRZ]);
		else
			MoveDynamicObject(worldGate[world][gateSlot][gID], worldGate[world][gateSlot][gPosStartX], worldGate[world][gateSlot][gPosStartY], worldGate[world][gateSlot][gPosStartZ], worldGate[world][gateSlot][gSpeed], worldGate[world][gateSlot][gPosStartRX], worldGate[world][gateSlot][gPosStartRY], worldGate[world][gateSlot][gPosStartRZ]);
	}
	else if(type == 1)
	{
		worldGate[world][gateSlot][gStatus] = true;
		MoveDynamicObject(worldGate[world][gateSlot][gID], worldGate[world][gateSlot][gPosEndX], worldGate[world][gateSlot][gPosEndY], worldGate[world][gateSlot][gPosEndZ], worldGate[world][gateSlot][gSpeed], worldGate[world][gateSlot][gPosEndRX], worldGate[world][gateSlot][gPosEndRY], worldGate[world][gateSlot][gPosEndRZ]);
	}
	else if(type == 2)
	{
		worldGate[world][gateSlot][gStatus] = false;
		MoveDynamicObject(worldGate[world][gateSlot][gID], worldGate[world][gateSlot][gPosStartX], worldGate[world][gateSlot][gPosStartY], worldGate[world][gateSlot][gPosStartZ], worldGate[world][gateSlot][gSpeed], worldGate[world][gateSlot][gPosStartRX], worldGate[world][gateSlot][gPosStartRY], worldGate[world][gateSlot][gPosStartRZ]);
	}

  return true;
}

CB:specialAction(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   actionid,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "d", actionid)) {
    return SendMissCBMessage(playerid, blockid, actionid, "actionid");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerSpecialAction(playerid, actionid);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerSpecialAction(targetid, actionid);
  }

   return true;
}

CB:SetEnum(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   slot,
        param,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "df", slot, param)) {
    return SendMissCBMessage(playerid, blockid, actionid, "slot param");
  }

  if (0 > slot > 26) {
    return SendErrorCBMessage(playerid, blockid, actionId, "slot", "0-26");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    pData[playerid][cbData][slot] = floatround(param);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	pData[targetid][cbData][slot] = floatround(param);
  }

   return true;
}

CB:AddEnum(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   slot,
        param,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "df", slot, param)) {
    return SendMissCBMessage(playerid, blockid, actionid, "slot param");
  }

  if (0 > slot > 26) {
    return SendErrorCBMessage(playerid, blockid, actionId, "slot", "0-26");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    pData[playerid][cbData][slot] += floatround(param);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	pData[targetid][cbData][slot] += floatround(param);
  }

   return true;
}

CB:SetClist(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   color,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "x", color)) {
    return SendMissCBMessage(playerid, blockid, actionid, "color");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    SetPlayerColor(playerid, color);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	SetPlayerColor(targetid, color);
  }

   return true;
}

CB:GameText(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   str[64],
        time,
        style,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dds[64]", time, style, str)) {
    return SendMissCBMessage(playerid, blockid, actionid, "time style string");
  }

  if (0 > style > 6) {
    return SendErrorCBMessage(playerid, blockid, actionid, "style", "0-6");
  }
  if (100 > time > 100000) {
    return SendErrorCBMessage(playerid, blockid, actionid, "time", "100-10000");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    GameTextForPlayer(targetid, str, time, style);
    return true;
  }

  foreach(new targetid : Player)
  {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

  	GameTextForPlayer(targetid, str, time, style);
  }

   return true;
}

CB:CreateExplosion(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new   type,
        Float: x,
        Float: y,
        Float: z,
        Float: radius,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dfF(0.0)F(0.0)F(0.0)", type, radius, x, y, z)) {
    return SendMissCBMessage(playerid, blockid, actionid, "type radius [x y z]");
  }

  if (0 > type > 13) {
    return SendErrorCBMessage(playerid, blockid, actionid, "type", "0-13");
  }
  if (0.1 > radius > 999.0) {
    return SendErrorCBMessage(playerid, blockid, actionid, "radius", "0.1-999.0");
  }

 	if(!x && !y && !z)
	{
		Streamer_GetFloatData(STREAMER_TYPE_AREA, cmBlock[world][blockid][cbID], E_STREAMER_X, x);
		Streamer_GetFloatData(STREAMER_TYPE_AREA, cmBlock[world][blockid][cbID], E_STREAMER_Y, y);
		Streamer_GetFloatData(STREAMER_TYPE_AREA, cmBlock[world][blockid][cbID], E_STREAMER_Z, z);
	}

  foreach(new targetid : Playerid) {
    if (!cbCompareMode(targetid, blockid, world)) {
     continue;
    }

    CreateExplosionForPlayer(targetid, x, y, z, type, radius);
  }

   return true;
}

CB:SetServer(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new  slot,
        Float: param,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "df", slot, param)) {
    return SendMissCBMessage(playerid, blockid, actionid, "slot param");
  }

  if (0 > slot > 51) {
    return SendErrorCBMessage(playerid, blockid, actionid, "slot", "0-50");
  }

  VW[world][vArray][slot] = floatround(param);

   return true;
}

CB:AddServer(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new  slot,
        Float: param,
        arguments[TEXT_FUNCTION_ARGUMENT];

  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "df", slot, param)) {
    return SendMissCBMessage(playerid, blockid, actionid, "slot param");
  }

  if (0 > slot > 51) {
    return SendErrorCBMessage(playerid, blockid, actionid, "slot", "0-50");
  }
  
  VW[world][vArray][slot] += floatround(param);

   return true;
}






// НОВЫЕ ФУНКЦИИ

CB:PlayCrimeReport(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new suspectid,
      crimeid,
      arguments[TEXT_FUNCTION_ARGUMENT];
    
    ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dd", suspectid, crimeid)) {
    return SendMissCBMessage(playerid, blockid, actionid, "suspectid crimeid");
  }

  if (0 > crimeid > 99) {
    return SendErrorCBMessage(playerid, blockid, actionid, "crimeid", "0-99");
  }

  if(!cmBlock[world][blockid][cbMode]) {
    PlayCrimeReportForPlayer(playerid, suspectid, crimeid);

    return true;
  }

  foreach(new targetid : Player) {
    if(!cbCompareMode(targetid, blockid, world)) {
      continue;
    }

    PlayCrimeReportForPlayer(targetid, suspectid, crimeid);
  }


  return true;
}


CB:InterpolateCamera(const playerid, const blockid, const actionid, const world, const argumentIdx) {
	new 	Float: startX,
		Float: startY,
		Float: startZ,
		Float: stopX,
		Float: stopY,
		Float: stopZ,
		mtime,
		meth,
		arguments[TEXT_FUNCTION_ARGUMENT];
	
	ReadAmxMemoryArray(argumentIdx, arguments);
	
	if (sscanf(arguments, "ffffffD(1000)D(0)", startX, startY, startZ, stopX, stopY, stopZ, mtime, meth)) {
    		return SendMissCBMessage(playerid, blockid, actionid, "startX startY startZ stopX stopY stopZ time method(0/1)");
  	}
	
	if(!cmBlock[world][blockid][cbMode]) {
		TogglePlayerSpectating(playerid, true);
		if(meth == 0)
			InterpolateCameraPos(playerid, startX, startY, startZ, stopX, stopY, stopZ, time, CAMERA_MOVE);
		else
			InterpolateCameraLookAt(playerid, startX, startY, startZ, stopX, stopY, stopZ, time, CAMERA_MOVE);
		
		return true;
	}
	
	foreach(new targetid : Player)
	{
		if (!cbCompareMode(targetid, blockid, world)) {
    		 continue;
    		}
		
		TogglePlayerSpectating(targetid, true);
		if(meth == 0)
			InterpolateCameraPos(targetid, startX, startY, startZ, stopX, stopY, stopZ, time, CAMERA_MOVE);
		else
			InterpolateCameraLookAt(targetid, startX, startY, startZ, stopX, stopY, stopZ, time, CAMERA_MOVE);
		
	}

	return true;
}


CB:RenameTeam(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new teamid,
      newname[36],
      arguments[TEXT_FUNCTION_ARGUMENT];
    
    ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "ds[36]", teamid, newname)) {
    return SendMissCBMessage(playerid, blockid, actionid, "teamid string");
  }

  if (1 > teamid > 20) {
    return SendErrorCBMessage(playerid, blockid, actionid, "teamid", "1-20");
  }
  teamid--;

  format(worldTeam[world][teamid][tName], sizeof(worldTeam[world][teamid][tName]), "%s", newname);

  return true;
}

CB:SetTeamSkin(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new teamid,
      newskin,
      arguments[TEXT_FUNCTION_ARGUMENT];
    
    ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dd", teamid, newskin)) {
    return SendMissCBMessage(playerid, blockid, actionid, "teamid skin");
  }

  if (1 > teamid > 20) {
    return SendErrorCBMessage(playerid, blockid, actionid, "teamid", "1-20");
  }
  teamid--;

  if (0 > newskin > 311) {
      return SendErrorCBMessage(playerid, blockid, actionId, "skin", "0-311"):
  }

  worldTeam[world][teamid][tSkin] = newskin;

  return true;
}

CB:SetTeamChannel(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new teamid,
      channel,
      arguments[TEXT_FUNCTION_ARGUMENT];
    
    ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dd", teamid, channel)) {
    return SendMissCBMessage(playerid, blockid, actionid, "teamid channel");
  }

  if (1 > teamid > 20) {
    return SendErrorCBMessage(playerid, blockid, actionid, "teamid", "1-20");
  }
  teamid--;

  if (0 > channel > 999) {
    return SendErrorCBMessage(playerid, blockid, actionId, "channel", "0-999"):
  }

  worldTeam[world][teamid][tChannel] = channel;

  return true;
}

CB:SetTeamHealth(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new teamid,
      health,
      arguments[TEXT_FUNCTION_ARGUMENT];
    
    ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dd", teamid, health)) {
    return SendMissCBMessage(playerid, blockid, actionid, "teamid health");
  }

  if (1 > teamid > 20) {
    return SendErrorCBMessage(playerid, blockid, actionid, "teamid", "1-20");
  }
  teamid--;

  if (1 > health > 100) {
    return SendErrorCBMessage(playerid, blockid, actionId, "health", "1-100"):
  }

  worldTeam[world][teamid][tHealth] = health;

  return true;
}

CB:SetTeamArmour(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new teamid,
      armour,
      arguments[TEXT_FUNCTION_ARGUMENT];
    
    ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dd", teamid, armour)) {
    return SendMissCBMessage(playerid, blockid, actionid, "teamid armour");
  }

  if (1 > teamid > 20) {
    return SendErrorCBMessage(playerid, blockid, actionid, "teamid", "1-20");
  }
  teamid--;

  if (0 > health > 100) {
    return SendErrorCBMessage(playerid, blockid, actionId, "armour", "0-100"):
  }

  worldTeam[world][teamid][tArmour] = armour;

  return true;
}


CB:SetTeamSpawn(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new Float: x,
      Float: y,
      Float: z,
      Float: angle,
      teamid,
      interior,
      arguments[TEXT_FUNCTION_ARGUMENT];
    
    ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dffffd", teamid, x, y, z, angle, interior)) {
    return SendMissCBMessage(playerid, blockid, actionid, "teamid x y z angle interior");
  }

  if (1 > teamid > 20) {
    return SendErrorCBMessage(playerid, blockid, actionid, "teamid", "1-20");
  }
  teamid--;

  if (0 > interior > 99) {
    return SendErrorCBMessage(playerid, blockid, actionId, "interior", "0-99"):
  }

  worldTeam[world][teamid][tSpawn][0] = x;
  worldTeam[world][teamid][tSpawn][1] = y;
  worldTeam[world][teamid][tSpawn][2] = z;
  worldTeam[world][teamid][tSpawn][3] = angle;

  worldTeam[world][teamid][tInt] = interior;

  return true;
}

CB:SetTeamFFire(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new ffire,
      teamid,
      arguments[TEXT_FUNCTION_ARGUMENT];
    
    ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "dd", teamid, ffire)) {
    return SendMissCBMessage(playerid, blockid, actionid, "teamid ffire");
  }

  if (1 > teamid > 20) {
    return SendErrorCBMessage(playerid, blockid, actionid, "teamid", "1-20");
  }
  teamid--;

  if (0 > ffire > 2) {
    return SendErrorCBMessage(playerid, blockid, actionId, "ffire", "0-2"):
  }

  if (ffire == 0) {
    worldTeam[world][teamid][tFFire] = !worldTeam[world][teamid][tFFire];
  } else if (ffie == 1) {
    worldTeam[world][teamid][tFFire] = False;
  } else if (ffire == 2) {
    worldTeam[world][teamid][tFFire] = True;
  }

  return true;
}
