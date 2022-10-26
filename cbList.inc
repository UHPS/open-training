/*
	CB:название переменной объявляется в cbFunctionArray.inc -> cmBlockList
	Затем записывается индетефикатор в категорию cbBlockSort_

	ReturnCommand(playerid, params, world); - Передает из params[] в cbReturnList.inc -> params[]
	Там происходит преобразование возвращаемых команд по типу #name# и т.д.

	Если функция может выполнятся на группу игроков есть проверка:
	if(cmBlock[world][blockid][cbMode])

	Передача ID игрока и ID блока для прохождения соответсвия игрока требованиям проверки в разделе "Группа игроков"
	if(!cbCompareMode(i, blockid))
*/


CB:setHealth(playerid, blockid, world, params[])
{
	new Float:hp;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "f", hp))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerHealth(i, hp);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerHealth(playerid, hp);
	return true;
}

CB:addHealth(playerid, blockid, world, params[])
{
	new Float:hp;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "f", hp))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerHealth(i, pData[i][pHealth] + hp);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerHealth(playerid, pData[playerid][pHealth] + hp);
	return true;
}

CB:setArmor(playerid, blockid, world, params[])
{
	new Float:arm;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "f", arm))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerArmour(i, arm);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerArmour(playerid, arm);
	return true;
}

CB:addArmor(playerid, blockid, world, params[])
{
	new Float:arm;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "f", arm))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerArmour(i, pData[i][pArmour] + arm);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerArmour(playerid, pData[playerid][pArmour] + arm);
	return true;
}

CB:setPos(playerid, blockid, world, params[])
{
	new Float:pos[4];
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "fff", pos[0], pos[1], pos[2]))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerPos(i, pos[0], pos[1], pos[2]);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	return true;
}

CB:setSkin(playerid, blockid, world, params[])
{
	new skin;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", skin))
		return CBWrongData(playerid, blockid, world);

	if(IsWorldUGMP(world))
	{
		if(!IsValidSkinUGMP(skin))
			return CBWrongData(playerid, blockid, world);
	}
	else
	{
		if(skin < 0 || skin > 311)
			return CBWrongData(playerid, blockid, world);
	}

	if(GetPlayerSkin(playerid) == skin)
		return true;

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			pData[i][pSkin] = skin;
			SetPlayerSkin(i, skin);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	pData[playerid][pSkin] = skin;
	SetPlayerSkin(playerid, skin);
	return true;
}

CB:setTime(playerid, blockid, world, params[])
{
	new time;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", time))
		return CBWrongData(playerid, blockid, world);

	if(time < 0 || time > 24)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerTime(i, time, 0);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerTime(playerid, time, 0);
	return true;
}

CB:setWeather(playerid, blockid, world, params[])
{
	new weather;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", weather))
		return CBWrongData(playerid, blockid, world);

	if(weather < 0 || weather > 255)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerWeather(i, weather);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerWeather(playerid, weather);
	return true;
}

CB:giveWeapon(playerid, blockid, world, params[])
{
	new
		weapon,
		ammo;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "dd", weapon, ammo))
		return CBWrongData(playerid, blockid, world);

	if(weapon > 46 || weapon < 0)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			GiveGun(i, weapon, ammo);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	GiveGun(playerid, weapon, ammo);
	return true;
}

CB:resetWeapon(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			ResetGun(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	ResetGun(playerid);
	return true;
}

CB:giveMoney(playerid, blockid, world, params[])
{
	new money;
	ReturnCommand(playerid, params, world);

	if (sscanf(params, "d", money))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			AddPlayerMoney(i, money);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	AddPlayerMoney(playerid, money);
	return true;
}

CB:resetMoney(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			pData[i][pMoney] = 0;
			ResetPlayerMoney(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	pData[playerid][pMoney] = 0;
	ResetPlayerMoney(playerid);
	return true;
}

CB:setSpawn(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SpawnPlayer(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SpawnPlayer(playerid);
	return true;
}

CB:sendMessage(playerid, blockid, world, params[])
{
	new str[144];
	ReturnCommand(playerid, params, world);

	if(VW[world][vDev])
		format(str, sizeof(str), "[CB:%d]: {FFFFFF}%s", blockid, params);
	else
		format(str, sizeof(str), "[CB]: {FFFFFF}%s", params);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SendClientMessage(i, COLOR_ORANGE, str);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SendClientMessage(playerid, COLOR_ORANGE, str);
	return true;
}

CB:playSound(playerid, blockid, world, params[])
{
	new
		sound,
		Float:x,
		Float:y,
		Float:z;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "dF(0)F(0)F(0)", sound, x, y, z))
		return CBWrongData(playerid, blockid, world);

	if(sound < 0 || sound > 65535)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			PlayerPlaySound(i, sound, x, y, z);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	PlayerPlaySound(playerid, sound, x, y, z);
	return true;
}

CB:setInterior(playerid, blockid, world, params[])
{
	new interior;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", interior))
		return CBWrongData(playerid, blockid, world);

	if(interior < 0 || interior > 99)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerInterior(i, interior);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerInterior(playerid, interior);
	return true;
}

CB:setChannel(playerid, blockid, world, params[])
{
	new channel;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", channel))
		return CBWrongData(playerid, blockid, world);

	if(channel < 0 || channel > 999)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			pData[i][pChannel] = channel;
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	pData[playerid][pChannel] = channel;
	return true;
}

CB:setTeam(playerid, blockid, world, params[])
{
	new teamid;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", teamid))
		return CBWrongData(playerid, blockid, world);

	if(teamid < 0 || teamid > MAX_WORLD_TEAM)
		return CBWrongData(playerid, blockid, world);

	teamid--;

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(worldTeam[world][teamid][tSkin])
				pData[i][pSkin] = worldTeam[world][teamid][tSkin];

			pData[i][pTeam] = teamid;
			SpawnZone(i);
			SpawnPlayer(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(pData[playerid][pTeam] == teamid)
		return true;

	pData[playerid][pTeam] = teamid;

	if(teamid != -1)
	{
		if(worldTeam[world][teamid][tSkin])
			pData[playerid][pSkin] = worldTeam[world][teamid][tSkin];
	}

	SpawnZone(playerid);
	SpawnPlayer(playerid);
	return true;
}

CB:setAnim(playerid, blockid, world, params[])
{
	new
		lib[16],
		anim[32],
		loop,
		freeze;

	if(sscanf(params, "s[16]s[32]ll", lib, anim, loop, freeze))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(freeze)
				ApplyAnimationEx(i, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);
			else
				ApplyAnimation(i, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(freeze)
		ApplyAnimationEx(playerid, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);
	else
		ApplyAnimation(playerid, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);

	return true;
}

CB:giveVehicle(playerid, blockid, world, params[])
{
	if(IsPlayerInAnyVehicle(playerid))
		return true;

	ReturnCommand(playerid, params, world);

	if(!IsValidWorld(world))
		return true;

	new
		interior = GetPlayerInterior(playerid),
		model[32],
		Float:playerPos[4],
		color1,
		color2,
		siren,
		vehicleid;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "s[32]I(-1)I(-1)D(0)", model, color1, color2, siren))
		return CBWrongData(playerid, blockid, world);

	if(IsWorldUGMP(world))
	{
		if((model[0] = GetVehicleModelByNameUGMP(model)) == 0)
			return CBWrongData(playerid, blockid, world);
	}
	else
	{
		if ((model[0] = GetVehicleModelByName(model)) == 0)
			return CBWrongData(playerid, blockid, world);
	}

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			GetPlayerPos(i, playerPos[0], playerPos[1], playerPos[2]);
			GetPlayerFacingAngle(i, playerPos[3]);

			vehicleid = CreateVehicleEx(model[0], playerPos, color1, color2, world, interior, siren);

			if(vehicleid == -1)
			{
				SendErrorMessage(playerid, "Достигнут лимит транспорта.");
				return CBWrongData(playerid, blockid, world);
			}

			pData[i][pRetVal][0] = vehicleid;

			vData[ tempWorld[world][vehSlot][vehicleid] ][vOwner] = pData[i][pID];
			vData[ tempWorld[world][vehSlot][vehicleid] ][vTeam] = -1;

			PutPlayerVeh(i, tempWorld[world][vehSlot][vehicleid], 0);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	GetPlayerFacingAngle(playerid, playerPos[3]);

	vehicleid = CreateVehicleEx(model[0], playerPos, color1, color2, world, interior, siren);

	if(vehicleid == -1)
	{
		SendErrorMessage(playerid, "Достигнут лимит транспорта.");
		return CBWrongData(playerid, blockid, world);
	}

	pData[playerid][pRetVal][0] = vehicleid;
	vData[ tempWorld[world][vehSlot][vehicleid] ][vOwner] = pData[playerid][pID];
	vData[ tempWorld[world][vehSlot][vehicleid] ][vTeam] = -1;

	PutPlayerVeh(playerid, tempWorld[world][vehSlot][vehicleid], 0);
	return true;
}

CB:setVehHP(playerid, blockid, world, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	new Float:health;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "f", health))
		return CBWrongData(playerid, blockid, world);

	if(health < 0 || health > 9999)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(!IsPlayerInAnyVehicle(i))
				continue;

			SetVehicleHealth(GetPlayerVehicleID(i), health);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetVehicleHealth(GetPlayerVehicleID(playerid), health);
	return true;
}

CB:SetVehData(playerid, blockid, world, params[])
{
	new
		vehicleid,
		slot,
		value;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "ddd", vehicleid, slot, value))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(vehicleid == 0 && IsPlayerInAnyVehicle(playerid))
		vehicleid = GetPlayerVehicleID(playerid);

	if(vehicleid < 1 || vehicleid > MAX_VEHICLES)
		return true;

	vData[vehicleid][vArray][slot] = value;
	return true;
}

CB:AddVehData(playerid, blockid, world, params[])
{
	new
		vehicleid,
		slot,
		value;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "ddd", vehicleid, slot, value))
		return CBWrongData(playerid, blockid, world);

	if(vehicleid < 1 || vehicleid > MAX_VEHICLES)
		return true;

	if(GetPlayerVirtualWorld(playerid) != world)
		return true;

	if(GetVehicleVirtualWorld(vehicleid) != world)
		return true;

	vData[vehicleid][vArray][slot] += value;
	return true;
}

CB:addVehHP(playerid, blockid, world, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	new
		Float:oldHealth,
		Float:health;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "f", health))
		return CBWrongData(playerid, blockid, world);

	if(health < -9999 || health > 9999)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(!IsPlayerInAnyVehicle(i))
				continue;

			GetVehicleHealth(GetPlayerVehicleID(i), oldHealth);
			health += oldHealth;

			if(health > 9999)
				health = 9999;

			SetVehicleHealth(GetPlayerVehicleID(i), health);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	GetVehicleHealth(GetPlayerVehicleID(playerid), oldHealth);
	health += oldHealth;

	if(health > 9999)
		health = 9999;

	SetVehicleHealth(GetPlayerVehicleID(playerid), health);
	return true;
}

CB:spawnVeh(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(!IsPlayerInAnyVehicle(i))
				continue;

			SetVehicleToRespawn(GetPlayerVehicleID(i));
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	SetVehicleToRespawn(GetPlayerVehicleID(playerid));
	return true;
}

CB:sprayVeh(playerid, blockid, world, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	ReturnCommand(playerid, params, world);

	new
		color1,
		color2;

	if(sscanf(params, "dd", color1, color2))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			ChangeVehicleColor(GetPlayerVehicleID(i), color1, color2);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	ChangeVehicleColor(GetPlayerVehicleID(playerid), color1, color2);
	return true;
}

CB:addVehComp(playerid, blockid, world, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	ReturnCommand(playerid, params, world);
	new vehComp;
	if(sscanf(params, "d", vehComp))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			AddVehicleComponent(GetPlayerVehicleID(i), vehComp);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	AddVehicleComponent(GetPlayerVehicleID(playerid), vehComp);
	return true;
}

CB:delVehComp(playerid, blockid, world, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	ReturnCommand(playerid, params, world);

	new vehComp;
	if(sscanf(params, "d", vehComp))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			RemoveVehicleComponent(GetPlayerVehicleID(i), vehComp);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	RemoveVehicleComponent(GetPlayerVehicleID(playerid), vehComp);
	return true;
}

CB:delVeh(playerid, blockid, world, params[])
{
	if(!IsValidWorld(world))
		return true;

	ReturnCommand(playerid, params, world);

	new vehicleid;
	sscanf(params, "d", vehicleid);

	if(vehicleid == 0)
	{
		if(!IsPlayerInAnyVehicle(playerid))
			return true;

		if(cmBlock[world][blockid][cbMode])
		{
			foreach(new i : Player)
			{
				if(world != GetPlayerVirtualWorld(i))
					continue;

				if(!cbCompareMode(i, blockid))
					continue;

				DestroyVehicleEx(GetPlayerVehicleID(i), world);
			}

			return true;
		}

		if(world != GetPlayerVirtualWorld(playerid))
			return true;

		DestroyVehicleEx(GetPlayerVehicleID(playerid), world);
	}
	else
	{
		if(vehicleid < 1 || vehicleid > MAX_VEHICLES)
			return CBWrongData(playerid, blockid, world);

		if(GetVehicleVirtualWorld(vehicleid) != world)
			return true;

		DestroyVehicleEx(vehicleid, world);
	}
	return true;
}

CB:fixVeh(playerid, blockid, world, params[])
{
	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	if(!IsValidWorld(world))
		return true;

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			new Float:health;
			GetVehicleHealth(GetPlayerVehicleID(i), health);

			RepairVehicle(GetPlayerVehicleID(i));
			SetVehicleHealth(GetPlayerVehicleID(i), health);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	new Float:health;
	GetVehicleHealth(GetPlayerVehicleID(playerid), health);

	RepairVehicle(GetPlayerVehicleID(playerid));
	SetVehicleHealth(GetPlayerVehicleID(playerid), health);
	return true;
}

CB:setScore(playerid, blockid, world, params[])
{
	new score;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", score))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerScore(i, score);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;


	SetPlayerScore(playerid, score);
	return true;
}

CB:addScore(playerid, blockid, world, params[])
{
	new score;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", score))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerScore(i, GetPlayerScore(i) + score);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerScore(playerid, GetPlayerScore(playerid) + score);
	return true;
}

CB:setWanted(playerid, blockid, world, params[])
{
	new level;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", level))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerWantedLevel(i, level);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerWantedLevel(playerid, level);
	return true;
}

CB:addWanted(playerid, blockid, world, params[])
{
	new level;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", level))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerWantedLevel(i, GetPlayerWantedLevel(i) + level);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + level);
	return true;
}

CB:SetPlayerCP(playerid, blockid, world, params[])
{
	new
		Float:pos[3],
		Float:size;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "ffff", pos[0], pos[1], pos[2], size))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerCheckpoint(i, pos[0], pos[1], pos[2], size);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerCheckpoint(playerid, pos[0], pos[1], pos[2], size);
	return true;
}

CB:DisablePlayerCP(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			DisablePlayerCheckpoint(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	DisablePlayerCheckpoint(playerid);
	return true;
}

CB:SetPlayerRaceCP(playerid, blockid, world, params[])
{
	new
		type,
		Float:pos[6],
		Float:size;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "dfffffff", type, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5], size))
		return CBWrongData(playerid, blockid, world);

	if(type < 0 || type > 8)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerRaceCheckpoint(i, type, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5], size);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerRaceCheckpoint(playerid, type, pos[0], pos[1], pos[2], pos[3], pos[4], pos[5], size);
	return true;
}

CB:DisablePlayerRaceCP(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			DisablePlayerRaceCheckpoint(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	DisablePlayerRaceCheckpoint(playerid);
	return true;
}

CB:SetPlayerMapIcon(playerid, blockid, world, params[])
{
	new
		iconid,
		Float:pos[3],
		markertype,
		color,
		style;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "dfffdxd", iconid, pos[0], pos[1], pos[2], markertype, color, style))
		return CBWrongData(playerid, blockid, world);

	if(iconid < 0 || iconid > 99)
		return CBWrongData(playerid, blockid, world);

	if(markertype < 0 || markertype > 63)
		return CBWrongData(playerid, blockid, world);

	if(style < 0 || style > 4)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerMapIcon(i, iconid, pos[0], pos[1], pos[2], markertype, color, style);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerMapIcon(playerid, iconid, pos[0], pos[1], pos[2], markertype, color, style);
	return true;
}

CB:RemovePlayerMapIcon(playerid, blockid, world, params[])
{
	new
		iconid;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", iconid))
		return CBWrongData(playerid, blockid, world);

	if(iconid < 0 || iconid > 99)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			RemovePlayerMapIcon(i, iconid);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	RemovePlayerMapIcon(playerid, iconid);
	return true;
}

CB:SetPlayerAttach(playerid, blockid, world, params[])
{
	new slotid;

	if(sscanf(params, "d", slotid))
		return CBWrongData(playerid, blockid, world);

	slotid--;
	if(slotid < 0 || slotid > 9)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(sscanf(params,"p< >ddddfffffffff",
				slotid,
				pAttach[i][slotid][0],
				pAttach[i][slotid][1],
				pAttach[i][slotid][2],

				fpAttach[i][slotid][0],
				fpAttach[i][slotid][1],
				fpAttach[i][slotid][2],
				fpAttach[i][slotid][3],
				fpAttach[i][slotid][4],
				fpAttach[i][slotid][5],
				fpAttach[i][slotid][6],
				fpAttach[i][slotid][7],
				fpAttach[i][slotid][8]
			) ) break;

			SetPlayerAttach(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(sscanf(params,"p< >ddddfffffffff",
		slotid,
		pAttach[playerid][slotid][0],
		pAttach[playerid][slotid][1],
		pAttach[playerid][slotid][2],

		fpAttach[playerid][slotid][0],
		fpAttach[playerid][slotid][1],
		fpAttach[playerid][slotid][2],
		fpAttach[playerid][slotid][3],
		fpAttach[playerid][slotid][4],
		fpAttach[playerid][slotid][5],
		fpAttach[playerid][slotid][6],
		fpAttach[playerid][slotid][7],
		fpAttach[playerid][slotid][8]
	) ) return CBWrongData(playerid, blockid, world);

	SetPlayerAttach(playerid);
	return true;
}


CB:DelPlayerAttach(playerid, blockid, world, params[])
{
	new slotid;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", slotid))
		return CBWrongData(playerid, blockid, world);

	if(slotid < 0 || slotid > 10)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(slotid == 0)
			{
				for(new t; t < 10; t++)
				{
					pAttach[i][t][0] = false;
					pAttach[i][t][1] = false;
					RemovePlayerAttachedObject(i, t);
				}
			}
			else
			{
				slotid--;
				pAttach[playerid][slotid][0] = false;
				pAttach[playerid][slotid][1] = false;
				RemovePlayerAttachedObject(i, slotid);
			}
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(slotid == 0)
	{
		for(new i; i < 10; i++)
		{
			pAttach[playerid][i][0] = false;
			pAttach[playerid][i][1] = false;
			RemovePlayerAttachedObject(playerid, i);
		}
	}
	else
	{
		slotid--;
		pAttach[playerid][slotid][0] = false;
		pAttach[playerid][slotid][1] = false;
		RemovePlayerAttachedObject(playerid, slotid);
	}
	return true;
}

CB:ActiveGate(playerid, blockid, world, params[])
{
	new
		gateSlot,
		type;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "dd", gateSlot, type))
		return CBWrongData(playerid, blockid, world);

	gateSlot--;
	if(gateSlot < 0 || gateSlot > MAX_WORLD_GATES || type < 0 || type > 3)
		return CBWrongData(playerid, blockid, world);

	if(!IsValidGate(world, gateSlot))
		return CBWrongData(playerid, blockid, world);


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

CB:SpecialAction(playerid, blockid, world, params[])
{
	new actionid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", actionid))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerSpecialAction(i, actionid);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerSpecialAction(playerid, actionid);
	return true;
}

CB:SetEnum(playerid, blockid, world, params[])
{
	new
		slot,
		Float:param;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "df", slot, param))
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > 26)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			pData[i][cbData][slot] = floatround(param);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	pData[playerid][cbData][slot] = floatround(param);
	return true;
}

CB:AddEnum(playerid, blockid, world, params[])
{
	new
		slot,
		Float:param;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "df", slot, param))
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > 26)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			pData[i][cbData][slot] += floatround(param);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	pData[playerid][cbData][slot] += floatround(param);
	return true;
}

CB:SetClist(playerid, blockid, world, params[])
{
	new color;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "x", color))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerColor(i, color);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerColor(playerid, color);
	return true;
}

CB:GameText(playerid, blockid, world, params[])
{
	new
		str[64],
		time,
		style;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dds[64]", time, style, str))
		return CBWrongData(playerid, blockid, world);

	if(time < 100 || time > 10000)
		return CBWrongData(playerid, blockid, world);

	if(style < 0 || style > 6)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			GameTextForPlayer(i, str, time, style);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	GameTextForPlayer(playerid, str, time, style);
	return true;
}

CB:CreateExplosion(playerid, blockid, world, params[])
{
	new
		type,
		Float:x,
		Float:y,
		Float:z,
		Float:radius;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dfF(0.0)F(0.0)F(0.0)", type, radius, x, y, z))
		return CBWrongData(playerid, blockid, world);

	if(type < 0 || type > 13)
		return CBWrongData(playerid, blockid, world);

	if(radius < 0.1 || radius > 9999.0)
		return CBWrongData(playerid, blockid, world);

	if(!x && !y && !z)
	{
		Streamer_GetFloatData(STREAMER_TYPE_AREA, cmBlock[world][blockid][cbID], E_STREAMER_X, x);
		Streamer_GetFloatData(STREAMER_TYPE_AREA, cmBlock[world][blockid][cbID], E_STREAMER_Y, y);
		Streamer_GetFloatData(STREAMER_TYPE_AREA, cmBlock[world][blockid][cbID], E_STREAMER_Z, z);
	}

	foreach(new i : Player)
	{
		if(world != GetPlayerVirtualWorld(i))
			continue;

		if(!cbCompareMode(i, blockid))
			continue;

		CreateExplosionForPlayer(i, x, y, z, type, radius);
	}

	return true;
}

CB:SetServer(playerid, blockid, world, params[])
{
	new
		slot,
		Float:param;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "df", slot, param))
	{
		return CBWrongData(playerid, blockid, world);
	}

	if(slot < 0 || slot > 51)
		return CBWrongData(playerid, blockid, world);

	VW[world][vArray][slot] = floatround(param);
	return true;
}

CB:AddServer(playerid, blockid, world, params[])
{

	new
		slot,
		Float:param;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "df", slot, param))
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > 51)
		return CBWrongData(playerid, blockid, world);

	VW[world][vArray][slot] += floatround(param);
	return true;
}

CB:EditAction(playerid, blockid, world, params[])
{	new
		slot,
		str[144];

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "ds[144]", slot, str))
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > MAX_WORLD_ACTION)
		return CBWrongData(playerid, blockid, world);

	if(Text3D:worldAction[world][slot][vAction] == Text3D:INVALID_3DTEXT_ID)
		return CBWrongData(playerid, blockid, world);

	new numStart;
	while(numStart != -1)
	{
		numStart = strfind(str, "@", true);
		if(numStart == -1)
			break;

		strdel(str, numStart, numStart + 1);
		strins(str, "\n", numStart, 144);
	}

	UpdateDynamic3DTextLabelText(worldAction[world][slot][vAction], COLOR_PURPLE, str);
	return true;
}

CB:DelAction(playerid, blockid, world, params[])
{
	new slot;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", slot))
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > MAX_WORLD_ACTION)
		return CBWrongData(playerid, blockid, world);

	if(Text3D:worldAction[world][slot][vAction] == Text3D:INVALID_3DTEXT_ID)
		return CBWrongData(playerid, blockid, world);

	DestroyDynamic3DTextLabel(worldAction[world][slot][vAction]);

	return true;
}

CB:MoveAction(playerid, blockid, world, params[])
{
	new
		Float:x,
		Float:y,
		Float:z,
		slot;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dfff", slot, x, y, z))
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > MAX_WORLD_ACTION)
		return CBWrongData(playerid, blockid, world);

	if(Text3D:worldAction[world][slot][vAction] == Text3D:INVALID_3DTEXT_ID)
		return CBWrongData(playerid, blockid, world);

	//DestroyDynamic3DTextLabel(worldAction[world][slot][vAction]);

	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, worldAction[world][slot][vAction], E_STREAMER_X, x);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, worldAction[world][slot][vAction], E_STREAMER_Y, y);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, worldAction[world][slot][vAction], E_STREAMER_Z, z);

	return true;
}

CB:FreezePlayer(playerid, blockid, world, params[])
{
	new time;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", time))
		return CBWrongData(playerid, blockid, world);

	if(time < -1 || time > 10000)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(time == -1)
				TogglePlayerControllable(i, 0);
			else
				ToFreeze(i, time);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(time == -1)
		TogglePlayerControllable(playerid, 0);
	else
		ToFreeze(playerid, time);
	return true;
}

CB:SetSkill(playerid, blockid, world, params[])
{
	new
		type,
		skill;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dd", type, skill))
		return CBWrongData(playerid, blockid, world);

	if(skill < 0 || skill > 999)
		return CBWrongData(playerid, blockid, world);

	if(type < 0 || type > 10)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerSkillLevel(i, type, skill);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerSkillLevel(playerid, type, skill);
	return true;
}

CB:SetStyle(playerid, blockid, world, params[])
{
	new
		type;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", type))
		return CBWrongData(playerid, blockid, world);

	if(type < 1 || type > 6)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			switch(type)
			{
				case 1: pData[i][pStyle] = 4;
				case 2: pData[i][pStyle] = 5;
				case 3: pData[i][pStyle] = 6;
				case 4: pData[i][pStyle] = 7;
				case 5: pData[i][pStyle] = 15;
				case 6: pData[i][pStyle] = 16;
			}

			FightStyle(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	switch(type)
	{
		case 1: pData[playerid][pStyle] = 4;
		case 2: pData[playerid][pStyle] = 5;
		case 3: pData[playerid][pStyle] = 6;
		case 4: pData[playerid][pStyle] = 7;
		case 5: pData[playerid][pStyle] = 15;
		case 6: pData[playerid][pStyle] = 16;
	}

	FightStyle(playerid);
	return true;
}

CB:KickPlayer(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerVw(i, 0);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerVw(playerid, 0);
	return true;
}


CB:BubblePlayer(playerid, blockid, world, params[])
{
	new
		text[128],
		time;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "ds[128]", time, text))
		return CBWrongData(playerid, blockid, world);

	if(time < 100 || time > 10000)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerChatBubble(i, text, 0xFFFFFFFF, 10.0, time);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerChatBubble(playerid, text, 0xFFFFFFFF, 10.0, time);
	return true;
}

CB:HideObject(playerid, blockid, world, params[])
{
	new
		objectid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", objectid))
		return CBWrongData(playerid, blockid, world);

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return CBWrongData(playerid, blockid, world);

	Streamer_ToggleItem(-1, STREAMER_TYPE_OBJECT, objectid, 0);
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	return true;
}

CB:ShowObject(playerid, blockid, world, params[])
{
	new
		objectid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", objectid))
		return CBWrongData(playerid, blockid, world);

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return CBWrongData(playerid, blockid, world);

	Streamer_ToggleItem(-1, STREAMER_TYPE_OBJECT, objectid, 1);
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	return true;
}

CB:WipeVehicle(playerid, blockid, world, params[])
{
	worldWipeFreeVeh(world);
	return true;
}

CB:SpawnVehicle(playerid, blockid, world, params[])
{
	worldSpawnFreeVeh(world);
	return true;
}

CB:SetGravity(playerid, blockid, world, params[])
{
	new
		Float:worldGravity;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "f", worldGravity))
		return CBWrongData(playerid, blockid, world);

	if(worldGravity > 0.1 || worldGravity < 0.00001)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerGravity(i, worldGravity);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerGravity(playerid, worldGravity);
	return true;
}

CB:GiveDamage(playerid, blockid, world, params[])
{
	new
		Float:damage;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "f", damage))
		return CBWrongData(playerid, blockid, world);

	if(damage < 0.1 || damage > 9999.0)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			AntiCheatGetHealth(i, pData[i][pHealth]);
			AntiCheatGetArmour(i, pData[i][pArmour]);

			if(pData[playerid][pArmour] > 0.0)
			{
				pData[i][pArmour] = (pData[i][pArmour] - damage);

				if(pData[i][pArmour] > 0.0)
				{
					SetPlayerArmour(i, pData[i][pArmour]);
				}else{
					SetPlayerArmour(i, 0);
					SetPlayerHealth(i, pData[i][pHealth] + pData[i][pArmour]);
				}

			}
			else
			{
				pData[i][pHealth] = (pData[i][pHealth] - damage);

				if(pData[i][pHealth] <= 0.9)
					SetPlayerHealth(i, 0.0);
				else
					SetPlayerHealth(i, pData[i][pHealth]);
			}
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	AntiCheatGetHealth(playerid, pData[playerid][pHealth]);
	AntiCheatGetArmour(playerid, pData[playerid][pArmour]);

	if(pData[playerid][pArmour] > 0.0)
	{
		pData[playerid][pArmour] = (pData[playerid][pArmour] - damage);

		if(pData[playerid][pArmour] > 0.0)
		{
			SetPlayerArmour(playerid, pData[playerid][pArmour]);
		}else{
			SetPlayerArmour(playerid, 0);
			SetPlayerHealth(playerid, pData[playerid][pHealth] + pData[playerid][pArmour]);
		}

	}
	else
	{
		pData[playerid][pHealth] = (pData[playerid][pHealth] - damage);

		if(pData[playerid][pHealth] <= 0.9)
			SetPlayerHealth(playerid, 0.0);
		else
			SetPlayerHealth(playerid, pData[playerid][pHealth]);
	}
	return true;
}

CB:SetDrunk(playerid, blockid, world, params[])
{
	new
		drunkLvl;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", drunkLvl))
		return CBWrongData(playerid, blockid, world);

	if(drunkLvl < 0 || drunkLvl > 50000)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerDrunkLevel(i, drunkLvl);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SetPlayerDrunkLevel(playerid, drunkLvl);
	return true;
}


CB:EditCallSign(playerid, blockid, world, params[])
{
	new
		str[144];

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "s[144]", str))
		return CBWrongData(playerid, blockid, world);

	new numStart;
	while(numStart != -1)
	{
		numStart = strfind(str, "@", true);
		if(numStart == -1)
			break;

		strdel(str, numStart, numStart + 1);
		strins(str, "\n", numStart, 144);
	}

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!IsPlayerInAnyVehicle(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			new
				Float:x,
				Float:y,
				Float:z,
				vehicleid = GetPlayerVehicleID(i);


			if(CallsignID[vehicleid] == Text3D:INVALID_3DTEXT_ID)
			{
				if(isBike(GetVehicleModel(vehicleid)))
				{
					x = -0.2;
					y = -1.2;
					z = 0.3;
				}
				else
				{
					x = -1;
					y = -2.8;
					z = -0.2;
				}

				CallsignID[vehicleid] = CreateDynamic3DTextLabel(str, COLOR_WHITE, x, y, z, 30.0, INVALID_PLAYER_ID, vehicleid, 0, world, -1, -1, -1);
			}
			else
			{
				UpdateDynamic3DTextLabelText(CallsignID[vehicleid], COLOR_WHITE, str);
			}
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	new
		Float:x,
		Float:y,
		Float:z,
		vehicleid = GetPlayerVehicleID(playerid);


	if(CallsignID[vehicleid] == Text3D:INVALID_3DTEXT_ID)
	{
		if(isBike(GetVehicleModel(vehicleid)))
		{
			x = -0.2;
			y = -1.2;
			z = 0.3;
		}
		else
		{
			x = -1;
			y = -2.8;
			z = -0.2;
		}

		CallsignID[vehicleid] = CreateDynamic3DTextLabel(str, COLOR_WHITE, x, y, z, 30.0, INVALID_PLAYER_ID, vehicleid, 0, world, -1, -1, -1);
	}
	else
	{
		UpdateDynamic3DTextLabelText(CallsignID[vehicleid], COLOR_WHITE, str);
	}

	return true;
}


CB:CallBlock(playerid, blockid, world, params[])
{
	new
		reval[3],
		userid,
		callBlock;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dD(-1)D(0)D(0)D(0)", callBlock, userid, reval[0], reval[1], reval[2]))
		return CBWrongData(playerid, blockid, world);

	if(callBlock < 0 || callBlock > VW[world][wMaxCB])
		return CBWrongData(playerid, blockid, world);


	if(userid < 0 || userid > MAX_PLAYERS)
		userid = playerid;

	if(GetPlayerVirtualWorld(userid) != world)
		userid = playerid;

	pData[playerid][pRetStr] = EOS;
	GetPlayerName(playerid, pData[userid][pRetStr][0], 24);

	pData[userid][pRetVal][0] = playerid;

	if(reval[0] != 0)
		pData[userid][pRetVal][1] = reval[0];

	if(reval[1] != 0)
		pData[userid][pRetVal][2] = reval[1];

	if(reval[2] != 0)
		pData[userid][pRetVal][3] = reval[2];

	pData[userid][pRetVal][4] = false;
	pData[userid][pRetVal][5] = false;
	pData[userid][pRetVal][6] = false;
	pData[userid][pRetVal][7] = false;
	pData[userid][pRetVal][8] = false;
	pData[userid][pRetVal][9] = false;

	OnCmBlockHandler(userid, callBlock, world, -1);
	return true;
}

CB:ObjectSetText(playerid, blockid, world, params[])
{
	new
		objectid,
		slotid,
		str[144];

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dds[144]", objectid, slotid, str))
		return CBWrongData(playerid, blockid, world);


	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return true;


	new
		text[1],
		materialsize,
		fontface[144],
		fontsize,
		bold,
		fontcolor,
		backcolor,
		textalignment,
		numStart;

	while(numStart != -1)
	{
		numStart = strfind(str, "@", true);
		if(numStart == -1)
			break;

		strdel(str, numStart, numStart + 1);
		strins(str, "\n", numStart, 144);
	}

	GetDynamicObjectMaterialText(objectid, slotid, text, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
	SetDynamicObjectMaterialText(objectid, slotid, str, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
	return true;
}

CB:ObjectSetColor(playerid, blockid, world, params[])
{
	new
		objectid,
		slotid,
		color;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "ddx", objectid, slotid, color))
		return true;

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return true;

	new
		txdmodel,
		txdname[64],
		texturename[64],
		textureColor;

	GetDynamicObjectMaterial(
		objectid,
		slotid,
		txdmodel,
		txdname,
		texturename,
		textureColor);

	TG_SetDynamicObjectMaterial(
		objectid,
		slotid,
		txdmodel,
		txdname,
		texturename,
		color);

	return true;
}


CB:CloneObject(playerid, blockid, world, params[])
{
	new
		objectid,
		modelid,
		Float:x,
		Float:y,
		Float:z,
		Float:rx,
		Float:rz,
		Float:ry;


	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dF(0.0)F(0.0)F(0.0)", objectid, x, y, z))
		return CBWrongData(playerid, blockid, world);


	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return true;

	modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID);

	if(x == 0.0 && y == 0.0 && z == 0.0)
		GetDynamicObjectPos(objectid, x, y, z);

	GetDynamicObjectRot(objectid, rx, ry, rz);

	new tempObject = addTempWorld(modelid, x, y, z, rx, ry, rz, world);

	if(tempObject == -1)
		return true;

	new cloneObject = VECTOR_get_val(WorldObjectSystem[world][wosObject], tempObject);

	for(new i; i < TEXTURE_SLOT; i++)
	{
		if(!IsDynamicObjectMaterialUsed(objectid, i))
			continue;

		new
			txdModel,
			txdName[32],
			texturename[32],
			materialcolor;

		GetDynamicObjectMaterial(objectid, i, txdModel, txdName, texturename, materialcolor);
		TG_SetDynamicObjectMaterial(cloneObject, i, txdModel, txdName, texturename, materialcolor);
	}

	pData[playerid][pRetVal][0] = tempObject;
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	return true;
}

CB:CreateObject(playerid, blockid, world, params[])
{
	new
		objectid,
		modelid,
		Float:x,
		Float:y,
		Float:z,
		Float:rx,
		Float:ry,
		Float:rz;


	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dfffF(0.0)F(0.0)F(0.0)", modelid, x, y, z, rx, ry, rz))
		return CBWrongData(playerid, blockid, world);

	if(!IsIDEValid(modelid))
		return CBWrongData(playerid, blockid, world);

	switch(modelid)
	{
		case 1382,1385,1379,1383,5126,1395,2983,2917,3474,1376,1393,1377,1391,1390,1389,1388,1387,1386,1384,1381,1380,1378,1392: return CBWrongData(playerid, blockid, world);
		case 1524..1531: return CBWrongData(playerid, blockid, world);
		case 1225: return CBWrongData(playerid, blockid, world);
	}

	objectid = addTempWorld(modelid, x, y, z, rx, ry, rz, world);

	if(objectid == -1)
		return CBWrongData(playerid, blockid, world);

	pData[playerid][pRetVal][0] = objectid;

	//Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	return true;
}

CB:SetTexture(playerid, blockid, world, params[])
{
	new
		objectid,
		slot,
		texture;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "ddd", objectid, slot, texture))
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > TEXTURE_SLOT)
		return CBWrongData(playerid, blockid, world);

	if(texture < 0 || texture > MAX_TEXTURES)
		return CBWrongData(playerid, blockid, world);

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return true;

	TG_SetDynamicObjectMaterial(
		objectid,
		slot,
		ObjectTextures[texture][TModel],
		ObjectTextures[texture][TXDName],
		ObjectTextures[texture][TextureName],
		0);


	return true;
}

CB:DelObject(playerid, blockid, world, params[])
{
	new
		slot,
		objectid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", slot))
		return CBWrongData(playerid, blockid, world);

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], slot);
	if(objectid <= 0)
		return true;

	/*
	if(tempWorld[world][tSlotText][objectid] != Text3D:INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(tempWorld[world][tSlotText][objectid]);
		tempWorld[world][tSlotText][objectid] = Text3D:INVALID_3DTEXT_ID;
	}
	*/

	DestroyDynamicObject(objectid);
	remTempWorld(world, slot);
	worldUpdateStreamer(world, STREAMER_TYPE_OBJECT);

	return true;
}

CB:MoveObject(playerid, blockid, world, params[])
{
	new
		objectid,
		Float:x,
		Float:y,
		Float:z,
		Float:rx,
		Float:rz,
		Float:ry,
		Float:speed;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dfffF(0.0)F(0.0)F(0.0)F(0.0)", objectid, x, y, z, speed, rx, ry, rz))
		return CBWrongData(playerid, blockid, world);

	if(speed < 0.0 || speed > 50.0)
		return CBWrongData(playerid, blockid, world);

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return CBWrongData(playerid, blockid, world);

	/*
	if(tempWorld[world][tSlotText][objectid] != Text3D:INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(tempWorld[world][tSlotText][objectid]);
		tempWorld[world][tSlotText][objectid] = Text3D:INVALID_3DTEXT_ID;
	}
	*/

	if(speed == 0.0)
	{
		SetDynamicObjectPos(objectid, x, y, z);
		SetDynamicObjectRot(objectid, rx, ry, rz);
	}
	else
	{
		MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
	}

	worldUpdateStreamer(pData[playerid][pWorld], STREAMER_TYPE_OBJECT);

	return true;
}

CB:setVehCollision(playerid, blockid, world, params[])
{
	new status;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", status))
		return CBWrongData(playerid, blockid, world);

	if(status != 0 && status != 1)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			DisableRemoteVehicleCollisions(i, status);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	DisableRemoteVehicleCollisions(playerid, status);
	return true;
}

CB:playStream(playerid, blockid, world, params[])
{
	new url[144];
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "s[144]", url))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			PlayAudioStreamForPlayer(i, url);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	PlayAudioStreamForPlayer(playerid, url);
	return true;
}

CB:SetModelObject(playerid, blockid, world, params[])
{
	new
		objectid,
		modelid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dd", objectid, modelid))
		return CBWrongData(playerid, blockid, world);

	if(!IsIDEValid(modelid))
		return CBWrongData(playerid, blockid, world);

	switch(modelid)
	{
		case 1382,1385,1379,1383,5126,1395,2983,2917,3474,1376,1393,1377,1391,1390,1389,1388,1387,1386,1384,1381,1380,1378,1392: return CBWrongData(playerid, blockid, world);
		case 1524..1531: return CBWrongData(playerid, blockid, world);
		case 1225: return CBWrongData(playerid, blockid, world);
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return CBWrongData(playerid, blockid, world);

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID, modelid);
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	return true;
}

CB:SelectObject(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

		    SelectObject(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	SelectObject(playerid);
	return true;
}

CB:EditObject(playerid, blockid, world, params[]) {
    new objectid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", objectid))
		return CBWrongData(playerid, blockid, world);

    if (objectid == 0) {
        SelectObject(playerid);
        return true;
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

    if(objectid <= 0)
		return CBWrongData(playerid, blockid, world);

    EditDynamicObject(playerid, objectid);

    return true;
}

CB:CancelEdit(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

		    CancelEdit(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	CancelEdit(playerid);
	return true;
}

CB:Create3DText(playerid, blockid, world, params[])
{
	new
		actText[144],
		Float:x,
		Float:y,
		Float:z;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "fffs[144]", x, y, z, actText))
		return CBWrongData(playerid, blockid, world);

	for(new i; i < MAX_WORLD_ACTION; i++)
	{
		if(Text3D:worldAction[world][i][vAction] != Text3D:INVALID_3DTEXT_ID)
			continue;

		new numStart;
		while(numStart != -1)
		{
			numStart = strfind(actText, "@", true);
			if(numStart == -1)
				break;

			strdel(actText, numStart, numStart + 1);
			strins(actText, "\n", numStart, 144);
		}

		worldAction[world][i][vAction]	= CreateDynamic3DTextLabel(actText, COLOR_PURPLE, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, worldAction[world][i][vAction], E_STREAMER_EXTRA_ID, i);

		pData[playerid][pRetVal][0] = i;
		tempWorld[world][vActionCount]++;

		return true;
	}

	return true;
}

CB:ShowDialog(playerid, blockid, world, params[])
{
	new
		callBlock,
		type,
		str[1024];

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dds[1024]", callBlock, type, str))
		return CBWrongData(playerid, blockid, world);

	if(callBlock < 0 || callBlock > VW[world][wMaxCB])
		return CBWrongData(playerid, blockid, world);

	if(type < 0 || type > 5)
		return CBWrongData(playerid, blockid, world);

	new numStart;

	while(numStart != -1)
	{
		numStart = strfind(str, "+", true);
		if(numStart == -1)
			break;

		strdel(str, numStart, numStart + 1);
		strins(str, "\t", numStart, 1024);
	}

	numStart = false;
	while(numStart != -1)
	{
		numStart = strfind(str, "@", true);
		if(numStart == -1)
			break;

		strdel(str, numStart, numStart + 1);
		strins(str, "\n", numStart, 1024);
	}

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			pData[i][pRetVal][10] = callBlock;
			Dialog_Show(i, CBMainDialog, type, "\t{FFFFFF}[ Командный блок ]", str, "Y", "X");
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	pData[playerid][pRetVal][10] = callBlock;
	Dialog_Show(playerid, CBMainDialog, type, "\t{FFFFFF}[ Командный блок ]", str, "Y", "X");
	return true;
}

CB:MoveCB(playerid, blockid, world, params[])
{
	new
		cbid,
		Float:x,
		Float:y,
		Float:z;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dfff", cbid, x, y, z))
		return CBWrongData(playerid, blockid, world);

	if(cbid < 0 || cbid > VW[world][wMaxCB])
		return CBWrongData(playerid, blockid, world);

	Streamer_SetFloatData(STREAMER_TYPE_AREA, cmBlock[world][cbid][cbID], E_STREAMER_X, x);
	Streamer_SetFloatData(STREAMER_TYPE_AREA, cmBlock[world][cbid][cbID], E_STREAMER_Y, y);
	Streamer_SetFloatData(STREAMER_TYPE_AREA, cmBlock[world][cbid][cbID], E_STREAMER_Z, z);
	return true;
}


CB:TimerOn(playerid, blockid, world, params[])
{
	new timerid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", timerid))
		return CBWrongData(playerid, blockid, world);

	if(timerid < 0 || timerid > MAX_CB_TIMER)
		return CBWrongData(playerid, blockid, world);

	timerid--;

	if(!CBTimer[world][timerid][cbtInterval])
		return CBWrongData(playerid, blockid, world);

	if(!CBTimer[world][timerid][cbtStatus])
	{
		CBTimer[world][timerid][cbtID] = SetTimerEx("cbtTimerHandler", CBTimer[world][timerid][cbtInterval], true, "dddd", playerid, world, timerid, CBTimer[world][timerid][cbtBlock]);
		CBTimer[world][timerid][cbtStatus] = true;
	}

	return true;
}

CB:TimerOff(playerid, blockid, world, params[])
{
	new timerid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", timerid))
		return CBWrongData(playerid, blockid, world);

	if(timerid < 0 || timerid > MAX_CB_TIMER)
		return CBWrongData(playerid, blockid, world);

	timerid--;

	if(CBTimer[world][timerid][cbtStatus])
	{
		KillTimer(CBTimer[world][timerid][cbtID]);
		CBTimer[world][timerid][cbtStatus] = false;
	}

	return true;
}

CB:GiveTaser(playerid, blockid, world, params[])
{
	new toggle;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", toggle))
		return CBWrongData(playerid, blockid, world);

	if(toggle < 0 || toggle > 1)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(toggle)
			{
				if(pData[i][pTazer])
					continue;

				pData[i][pTazer] = true;

				pData[i][pGuns][2] = dgun[i][weapon_slot][2];
				pData[i][pAmmo][2] = dgun[i][ammo_slot][2];

				GiveGun(i, 23, 1);
			}
			else
			{
				if(!pData[i][pTazer])
					continue;

				pData[i][pTazer] = false;

				if(pData[i][pGuns][2])
					GiveGun(i, pData[i][pGuns][2], pData[i][pAmmo][2]);
				else
					GiveGun(i, 24, 0);
			}
		}

		return true;
	}

	if(toggle)
	{
		if(pData[playerid][pTazer])
			return true;

		pData[playerid][pTazer] = true;
		pData[playerid][pGuns][2] = dgun[playerid][weapon_slot][2];
		pData[playerid][pAmmo][2] = dgun[playerid][ammo_slot][2];

		GiveGun(playerid, 23, 1);
	}
	else
	{
		if(!pData[playerid][pTazer])
			return true;

		pData[playerid][pTazer] = false;

		if(pData[playerid][pGuns][2])
			GiveGun(playerid, pData[playerid][pGuns][2], pData[playerid][pAmmo][2]);
		else
			GiveGun(playerid, 24, 0);
	}

	return true;
}

CB:SetPlate(playerid, blockid, world, params[])
{
	new str[32];

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "s[32]", str))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(GetPlayerVehicleSeat(i) != 0)
				continue;

			SetVehicleNumberPlate(GetPlayerVehicleID(i), str);
			SetVehicleToRespawn(GetPlayerVehicleID(i));
		}

		return true;
	}

	if(GetPlayerVehicleSeat(playerid) != 0)
		return true;

	SetVehicleNumberPlate(GetPlayerVehicleID(playerid), str);
	SetVehicleToRespawn(GetPlayerVehicleID(playerid));

	return true;
}

CB:SetOwner(playerid, blockid, world, params[])
{
	new
		ownerid,
		vehicleid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dd", vehicleid, ownerid))
		return CBWrongData(playerid, blockid, world);

	if(ownerid < 0 || ownerid > MAX_PLAYERS)
		return CBWrongData(playerid, blockid, world);

	if(vehicleid < 1 || vehicleid > MAX_VEHICLES)
		return CBWrongData(playerid, blockid, world);

	if(GetPlayerVirtualWorld(ownerid) != world)
		return true;

	if(GetVehicleVirtualWorld(vehicleid) != world)
		return true;

	vData[vehicleid][vOwner] = pData[ownerid][pID];
	return true;
}

CB:SetVehicleAttach(playerid, blockid, world, params[])
{
	new
		slotid,
		modelid,
		Float:x,
		Float:y,
		Float:z,
		Float:rx,
		Float:ry,
		Float:rz;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "ddffffff", slotid, modelid, x, y, z, rx, ry, rz))
		return CBWrongData(playerid, blockid, world);

	slotid--;
	if(slotid < 0 || slotid > 9)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(!IsPlayerInAnyVehicle(i))
				continue;

			if(GetPlayerVehicleSeat(i) != 0)
				continue;

			new vehicleid = GetPlayerVehicleID(i);

			if(vData[vehicleid][vattach][slotid])
			{
				Streamer_SetIntData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_MODEL_ID, modelid),
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_OFFSET_X, x);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_OFFSET_Y, y);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_OFFSET_Z, z);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_R_X, rx);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_R_Y, ry);
				Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_R_Z, rz);
			}
			else
			{
				vData[vehicleid][vattach][slotid] = CreateDynamicObject(modelid, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, world);
				AttachDynamicObjectToVehicle(vData[vehicleid][vattach][slotid], vehicleid, x, y, z, rx, ry, rz);
			}

		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	if(GetPlayerVehicleSeat(playerid) != 0)
		return true;

	new vehicleid = GetPlayerVehicleID(playerid);

	if(vData[vehicleid][vattach][slotid])
	{
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_MODEL_ID, modelid),
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_OFFSET_X, x);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_OFFSET_Y, y);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_OFFSET_Z, z);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_R_X, rx);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_R_Y, ry);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid] ,E_STREAMER_ATTACH_R_Z, rz);
	}
	else
	{
		vData[vehicleid][vattach][slotid] = CreateDynamicObject(modelid, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, world);
		AttachDynamicObjectToVehicle(vData[vehicleid][vattach][slotid], vehicleid, x, y, z, rx, ry, rz);
	}
	return true;
}

CB:UnVehicleAttach(playerid, blockid, world, params[])
{
	new slotid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", slotid))
		return CBWrongData(playerid, blockid, world);

	slotid--;
	if(slotid < 0 || slotid > 9)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(!IsPlayerInAnyVehicle(i))
				continue;

			if(GetPlayerVehicleSeat(i) != 0)
				continue;

			new vehicleid = GetPlayerVehicleID(i);

			if(vData[vehicleid][vattach][slotid])
			{
				if(IsValidDynamicObject(vData[vehicleid][vattach][slotid]))
					DestroyDynamicObject(vData[vehicleid][vattach][slotid]);

				vData[vehicleid][vattach][slotid] = false;
			}
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	if(GetPlayerVehicleSeat(playerid) != 0)
		return true;

	new vehicleid = GetPlayerVehicleID(playerid);

	if(vData[vehicleid][vattach][slotid])
	{
		if(IsValidDynamicObject(vData[vehicleid][vattach][slotid]))
			DestroyDynamicObject(vData[vehicleid][vattach][slotid]);

		vData[vehicleid][vattach][slotid] = false;
	}

	return true;
}

CB:SetVehiclePos(playerid, blockid, world, params[])
{
	new
		vehicleid,
		Float:x,
		Float:y,
		Float:z,
		Float:rx;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dfffF(0.0)", vehicleid, x, y, z, rx))
		return CBWrongData(playerid, blockid, world);

	if(vehicleid < 1 || vehicleid > MAX_VEHICLES)
		return CBWrongData(playerid, blockid, world);

	if(GetPlayerVirtualWorld(playerid) != world)
		return true;

	if(GetVehicleVirtualWorld(vehicleid) != world)
		return true;


	SetVehiclePos(vehicleid, x, y, z);
	SetVehicleZAngle(vehicleid, rx);
	return true;
}

CB:SetPlayerAngle(playerid, blockid, world, params[])
{
	new Float:Angle;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "f", Angle))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			SetPlayerFacingAngle(i, Angle);
		}

		return true;
	}

	SetPlayerFacingAngle(playerid, Angle);
	return true;
}


CB:SetNameTag(playerid, blockid, world, params[])
{
	new status;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", status))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(status != 0 && status != 1)
		return CBWrongData(playerid, blockid, world);

	foreach (new i : Player)
		ShowPlayerNameTagForPlayer(playerid, i, status);

	status = !status;
	pData[playerid][pHideName] = status;
	return true;
}

CB:ActorCreate(playerid, blockid, world, params[])
{
	new
		skin,
		Float:x,
		Float:y,
		Float:z,
		Float:rx;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dffff", skin, x, y, z, rx))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(skin < 0 || skin > 311)
		return CBWrongData(playerid, blockid, world);

	pData[playerid][pRetVal][0] = addTempActor(world, skin, x, y, z, rx, world, -1);
	return true;
}

CB:ActorDelete(playerid, blockid, world, params[])
{
	new actorid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", actorid))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT)
		return CBWrongData(playerid, blockid, world);

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid]))
		return true;

	if(actorSystem[ tempWorld[world][aSlot][actorid] ][aNameID] != Text3D:INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(actorSystem[ tempWorld[world][aSlot][actorid] ][aNameID]);
	}

	DestroyDynamicActor(tempWorld[world][aSlot][actorid]);

	actorSystem[ tempWorld[world][aSlot][actorid] ][localID] 	= false;
	actorSystem[ tempWorld[world][aSlot][actorid] ][aStatus] 	= false;
	actorSystem[ tempWorld[world][aSlot][actorid] ][UsedAnim] 	= false;
	actorSystem[ tempWorld[world][aSlot][actorid] ][AltAnim] 	= false;
	actorSystem[ tempWorld[world][aSlot][actorid] ][aNameID] 	= Text3D:INVALID_3DTEXT_ID;

	tempWorld[world][aSlot][actorid] = false;
	return true;
}

CB:ActorSetSkin(playerid, blockid, world, params[])
{
	new
		actorid,
		skin;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dd", actorid, skin))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT)
		return CBWrongData(playerid, blockid, world);

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid]))
		return true;

	Streamer_SetIntData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_MODEL_ID, skin);
	return true;
}

CB:ActorSetPos(playerid, blockid, world, params[])
{
	new
		actorid,
		Float:x,
		Float:y,
		Float:z;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dfff", actorid, x, y, z))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT)
		return CBWrongData(playerid, blockid, world);

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid]))
		return true;

	if(actorSystem[ tempWorld[world][aSlot][actorid] ][aNameID] != Text3D:INVALID_3DTEXT_ID)
	{
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, actorSystem[ tempWorld[world][aSlot][actorid] ][aNameID], E_STREAMER_X, x);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, actorSystem[ tempWorld[world][aSlot][actorid] ][aNameID], E_STREAMER_Y, y);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, actorSystem[ tempWorld[world][aSlot][actorid] ][aNameID], E_STREAMER_Z, z+1.1);
	}

	SetDynamicActorPos(tempWorld[world][aSlot][actorid], x, y, z);
	return true;
}

CB:ActorSetAngle(playerid, blockid, world, params[])
{
	new
		actorid,
		Float:rx;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "df", actorid, rx))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT)
		return CBWrongData(playerid, blockid, world);

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid]))
		return true;

	SetDynamicActorFacingAngle(tempWorld[world][aSlot][actorid], rx);
	return true;
}

CB:ActorSetAnim(playerid, blockid, world, params[])
{
	new
		actorid,
		animid;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dd", actorid, animid))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT)
		return CBWrongData(playerid, blockid, world);

	if(animid < 0 || animid > sizeof(actorAnim))
		return CBWrongData(playerid, blockid, world);

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid]))
		return true;

	ApplyDynamicActorAnimation(tempWorld[world][aSlot][actorid], actorAnim[animid][aLib], actorAnim[animid][aAnim], actorAnim[animid][aDelta], actorAnim[animid][aLoop], 0, 0, actorAnim[animid][aFreeze], 0);
	actorSystem[ tempWorld[world][aSlot][actorid] ][UsedAnim] = animid;

	SetDynamicActorHealth(tempWorld[world][aSlot][actorid], 100.0);
	return true;
}

CB:PlayerRess(playerid, blockid, world, params[])
{
	ReturnCommand(playerid, params, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			World_PlayerReviwe(i);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	World_PlayerReviwe(playerid);
	return true;
}

CB:PlayerSetDeath(playerid, blockid, world, params[])
{
	new time;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", time))
		return CBWrongData(playerid, blockid, world);

	if(time < 0 || time > 999)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			pData[i][pDead] = true;
			pData[i][pDeadStage] = time;
			GetPlayerPos(i, pData[i][pDeadX], pData[i][pDeadY], pData[i][pDeadZ]);
		}

		return true;
	}

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	pData[playerid][pDead] = true;
	pData[playerid][pDeadStage] = time;
	GetPlayerPos(playerid, pData[playerid][pDeadX], pData[playerid][pDeadY], pData[playerid][pDeadZ]);
	return true;
}

CB:setWorldTime(playerid, blockid, world, params[])
{
	new time;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", time))
		return CBWrongData(playerid, blockid, world);

	if(time < 0 || time > 24)
		return CBWrongData(playerid, blockid, world);

	VW[world][vTime] = time;
	foreach (new i : Player)
	{
		if(GetPlayerVirtualWorld(i) == world)
			SetPlayerTime(i, time, 0);
	}

	return true;
}

CB:setWorldWeather(playerid, blockid, world, params[])
{
	new weather;
	ReturnCommand(playerid, params, world);

	if(sscanf(params, "d", weather))
		return CBWrongData(playerid, blockid, world);

	if(weather < 0 || weather > 255)
		return CBWrongData(playerid, blockid, world);

	VW[world][vWeather] = weather;

	foreach (new i : Player)
	{
		if(GetPlayerVirtualWorld(i) == world)
			SetPlayerWeather(i, weather);
	}

	return true;
}

CB:VehicleStatus(playerid, blockid, world, params[])
{
	new
		slot,
		status;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dd", slot, status))
		return CBWrongData(playerid, blockid, world);

	if(status != 0 && status != 1)
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > 6)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;


			SetVehicleParams(GetPlayerVehicleID(i), slot, status);
		}

		return true;
	}

	SetVehicleParams(GetPlayerVehicleID(playerid), slot, status);
	return true;
}

CB:VehWindowStatus(playerid, blockid, world, params[])
{
	new
		slot,
		status;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "dd", slot, status))
		return CBWrongData(playerid, blockid, world);

	if(status != 0 && status != 1)
		return CBWrongData(playerid, blockid, world);

	if(slot < 0 || slot > 3)
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;


			SetVehicleWindow(GetPlayerVehicleID(i), slot, status);
		}

		return true;
	}

	SetVehicleWindow(GetPlayerVehicleID(playerid), slot, status);
	return true;
}


CB:SetVehicleTires(playerid, blockid, world, params[])
{
	new
		wheels[4];

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "dddd", wheels[0], wheels[1], wheels[2], wheels[3]))
		return CBWrongData(playerid, blockid, world);

	for(new i; i < sizeof(wheels); i++)
	{
		if(wheels[i] < 0 || wheels[i] > 2)
			return CBWrongData(playerid, blockid, world);
	}

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(world != GetPlayerVirtualWorld(i))
				continue;

			if(!cbCompareMode(i, blockid))
				continue;

			if(!IsPlayerInAnyVehicle(i))
				continue;

			if(GetPlayerVehicleSeat(i) != 0)
				continue;

			new
				tempTires[4],
				panels, doors, lights, tires;

			GetVehicleDamageStatus(GetPlayerVehicleID(i), panels, doors, lights, tires);
			decode_tires(tires, tempTires[0], tempTires[1], tempTires[2], tempTires[3]);

			for(new wheel; wheel < sizeof(wheels); wheel++)
			{
				if(wheels[wheel] == 2)
					continue;

				tempTires[wheel] = wheels[i];
			}

			UpdateVehicleDamageStatus(GetPlayerVehicleID(i), panels, doors, lights, encode_tires(tempTires[0], tempTires[1], tempTires[2], tempTires[3]) );
		}

		return true;
	}

	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	if(GetPlayerVehicleSeat(playerid) != 0)
		return true;

	new
		tempTires[4],
		panels, doors, lights, tires;

	GetVehicleDamageStatus(GetPlayerVehicleID(playerid), panels, doors, lights, tires);
	decode_tires(tires, tempTires[0], tempTires[1], tempTires[2], tempTires[3]);

	for(new i; i < sizeof(wheels); i++)
	{
		if(wheels[i] == 2)
			continue;

		tempTires[i] = wheels[i];
	}

	UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid), panels, doors, lights, encode_tires(tempTires[0], tempTires[1], tempTires[2], tempTires[3]) );
	return true;
}

CB:PutPlayerInVeh(playerid, blockid, world, params[])
{
	new
		vehicleid,
		slot;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "dd", vehicleid, slot))
		return CBWrongData(playerid, blockid, world);

	if(vehicleid < 1 || vehicleid > MAX_VEHICLES)
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;

	if(GetVehicleVirtualWorld(vehicleid) != world)
		return true;

	PutPlayerVeh(playerid, vehicleid, slot);
	return true;
}

CB:KickPlayerFromVeh(playerid, blockid, world, params[])
{
	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(!IsPlayerInAnyVehicle(i))
				continue;

			RemovePlayerFromVehicle(i);
		}
	}

	if(!IsPlayerInAnyVehicle(playerid))
		return true;

	RemovePlayerFromVehicle(playerid);
	return true;
}


CB:SetPlayerPvar(playerid, blockid, world, params[])
{
	new
		userid,
		var[32],
		data[144];

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "p<,>ds[32]s[144]", userid, var, data))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(userid))
		return true;

	if(updatePlayerVarData(userid, var, data) == INVALID_VECTOR_INDEX)
		return CBWrongData(playerid, blockid, world);

	return true;
}

CB:SetPvar(playerid, blockid, world, params[])
{
	new
		var[32],
		data[144];

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "p<,>s[32]s[144]", var, data))
		return CBWrongData(playerid, blockid, world);

	if(setVarData(world, var, data) == INVALID_VECTOR_INDEX)
		return CBWrongData(playerid, blockid, world);

	return true;
}

CB:SetPlayerWorldMute(playerid, blockid, world, params[])
{
	new
		userid,
		time;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "p<,>dD(65535)", time, userid))
		return CBWrongData(playerid, blockid, world);

	if(time < 0 || time > 10000)
		return CBWrongData(playerid, blockid, world);

	if(!IsPlayerOnline(userid))
		userid = playerid;

	if(GetPlayerVirtualWorld(userid) != world)
		userid = playerid;

	pData[userid][pWorldMute] = gettime() + time*60;

	return true;
}

CB:SetPlayerCameraPos(playerid, blockid, world, params[])
{
	new
		Float:x, Float:y, Float:z,
		Float:atX, Float:atY, Float:atZ;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "ffffff", x, y, z, atX, atY, atZ))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(GetPlayerVirtualWorld(i) != world)
				continue;

			TogglePlayerSpectating(i, true);
			SetPlayerCameraPos(i, x, y, z);
			SetPlayerCameraLookAt(i, atX, atY, atZ);
		}
	}

	TogglePlayerSpectating(playerid, true);
	SetPlayerCameraPos(playerid, x, y, z);
	SetPlayerCameraLookAt(playerid, atX, atY, atZ);

	return true;
}

CB:SetPlayerCameraLookAt(playerid, blockid, world, params[])
{
	new
		Float:x, Float:y, Float:z;

	ReturnCommand(playerid, params, world);

	if(sscanf(params, "fff", x, y, z))
		return CBWrongData(playerid, blockid, world);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(GetPlayerVirtualWorld(i) != world)
				continue;

			SetPlayerCameraLookAt(i, x, y, z);
		}
	}

	SetPlayerCameraLookAt(playerid, x, y, z);

	return true;
}

CB:ReturnPlayerCamera(playerid, blockid, world, params[])
{
	TogglePlayerSpectating(playerid, false);
	SetCameraBehindPlayer(playerid);

	if(cmBlock[world][blockid][cbMode])
	{
		foreach(new i : Player)
		{
			if(GetPlayerVirtualWorld(i) != world)
				continue;

			TogglePlayerSpectating(i, false);
			SetCameraBehindPlayer(i);
		}
	}

	return true;
}

CB:CallTriggerBlock(playerid, blockid, world, params[])
{
	new
		callBlock[24],
		data;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "p<,>s[24]d", callBlock, data))
		return CBWrongData(playerid, blockid, world);

	if(OnCallSwitchBlock(playerid, callBlock, world, data) == 0)
		return CBWrongData(playerid, blockid, world);

	return true;
}

CB:SetPlayerWorld(playerid, blockid, world, params[])
{
	if(!pData[playerid][pAdmin]) {
		return SendServerMessage(playerid, "Функционал находится в тесте");
	}

	new worldId, worldPass[64];
	if(sscanf(params, "ds[64]", worldId, worldPass)) {
		return CBWrongData(playerid, blockid, world);
	}

	if(!IsValidWorld(worldId)) {
		return SendServerMessage(playerid, "[DEBUG CB]: Данного мира не существует");
	}

	if(strcmp(worldPass, VW[world][wPassword], true)) {
		return SendServerMessage(playerid, "[DEBUG CB]: Неправильный пароль мира");
	}

	SetPlayerVw(playerid, worldId);

	return true;
}

CB:SetObjectArray(playerid, blockid, world, params[]) {
	new objectid, value;

	ReturnCommand(playerid, params, world);

	if (sscanf(params, "dd", objectid, value)) {
		return CBWrongData(playerid, blockid, world);
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
	if(objectid <= 0)
		return CBWrongData(playerid, blockid, world);

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_CUSTOM(1237), value);

	return true;
}

/*
CB:donate(playerid, params[])
{
	new amount;

	ReturnCommand(playerid, params, world);
	if(sscanf(params, "d", amount))
		return CBWrongData(playerid, blockid, world);

	if(world != GetPlayerVirtualWorld(playerid))
		return true;


	return true;
}
*/

/*

CB:CreateGangZone(playerid, blockid, world, params[])
{
	new
		slotid,
		Float:minx,
		Float:miny,
		Float:maxx,
		Float:maxy;

	if(sscanf(params, "ddffffff", slotid, modelid, x, y, z, rx, ry, rz))
		return CBWrongData(playerid, blockid, world);

	PlayerGangZoneCreate(playerid, Float:minx, Float:miny, Float:maxx, Float:maxy);
	return true;
}
*/
