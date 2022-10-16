/**
    resolveTargetOrSelf(playerid, argumentIdx) - Возвращает указанного игрока или инициатора форматируя его за вас.
    Пример:
        #money(10)# -> resolveTargetOrSelf(playerid, argumentIdx) -> targetid = 10
        #money# -> resolveTargetOrSelf(playerid, argumentIdx) -> targetid = playerid
    * Обратите внимания на функцию CBF:money там нет sscanf потому что эта функция сама форматирует это.
    ** Это сделано для того что не дублировать код где проверяется есть ли указанный id или нет.
    getTargetIdOrSelf(playerid, targetid) - Возвращает указанного игрока или инициатора.
    Пример:
        if (sscanf(arguments, "dD(-1)", targetid, weaponSlot)) {
            targetid = playerid;
        } else {
            targetid = getTargetIdOrSelf(playerid, targetid);
        }
    * Почти тоже самое что и выше, но необходимо для случаев где есть необязательные параметры или первый вариант не подходит.
    ReadAmxMemoryArray(argumentIdx, arguments) - функция которая получает переменную по индексу, особенность сампа.
    WriteAmxMemoryArray(resultIdx, value) - записываем строку с результатом по индексу переменной, так же особенность сампа.
*/


CBF:random(const playerid, const argumentIdx, const resultIdx)
{
    new
        arguments[TEXT_FUNCTION_ARGUMENT], // Строка аргументов в скобках. К примеру #random(1, 100)# сюда будет записано: 1, 100
        value[MAX_VALUE_SIZE], // Строка с результатом.
        startNumber, // Первый входящий Int параметр
        endNumber; // Второй входящий Int параметр

    ReadAmxMemoryArray(argumentIdx, arguments); // В функцию приходит индекс переменной с аргументами, поэтому нам необходимо его извлечь

    if (!sscanf(arguments, "p<,>dd", startNumber, endNumber)) { // Распарсиваем строку, если есть аргументы то используем для рандома их
        valstr(value, RandomEx(startNumber, endNumber));
    } else {
        valstr(value, random(100)); // иначе от 0 до 100 генерируем число, чтобы не сыпать ошибку людям
    }

    WriteAmxMemoryArray(resultIdx, value); // записываем результат в переменную по его индексу
    return true;
}

CBF:array(const playerid, const argumentIdx, const resultIdx)
{
    new
        arguments[TEXT_FUNCTION_ARGUMENT],
        value[MAX_VALUE_SIZE],
        arraySlot;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", arraySlot)) {
        return false;
    }

    if (0 > arraySlot > MAX_PLAYER_ARRAY_SLOT) {
        return false;
    }

    valstr(value, pData[playerid][cbData][arraySlot]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:server(const playerid, const argumentIdx, const resultIdx)
{
    new
        world = GetPlayerVirtualWorld(playerid),
        arguments[TEXT_FUNCTION_ARGUMENT],
        value[MAX_VALUE_SIZE],
        arraySlot;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", arraySlot)) {
        return false;
    }

    if (0 > arraySlot > MAX_WORLD_ARRAY_SLOT) {
        return false;
    }

    valstr(value, VW[world][vArray][arraySlot]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:var(const playerid, const argumentIdx, const resultIdx)
{
    new
        arguments[TEXT_FUNCTION_ARGUMENT],
        value[MAX_VALUE_SIZE],
        varValue[MAX_VAR_DATA_LEN];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "s[32]", varValue)) {
        return false;
    }

    if (getVarData(playerid, varValue, value) == INVALID_VECTOR_INDEX) {
        return false;
    }

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:pvar(const playerid, const argumentIdx, const resultIdx)
{
    new
        targetid,
        arguments[TEXT_FUNCTION_ARGUMENT],
        value[MAX_VALUE_SIZE],
        varValue[MAX_VAR_DATA_LEN];

    ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "p<,>s[32]d", varValue, targetid)) {
        targetid = playerid;
    }

    if (!IsPlayerOnline(targetid)) {
        return false;
    }

    if (sscanf(arguments, "s[32]", varValue)) {
        return false;
    }

    if (getPlayerVarData(targetid, varValue, value) == INVALID_VECTOR_INDEX) {
        return false;
    }

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:vdata(const playerid, const argumentIdx, const resultIdx)
{
    new
        arguments[TEXT_FUNCTION_ARGUMENT],
        value[MAX_VALUE_SIZE],
        vehicleId,
        vehicleSlot;

    ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "dd", vehicleId, vehicleSlot)) {
        return false;
    }

    if (!IsValidVehicle(vehicleId)) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        vehicleId = GetPlayerVehicleID(playerid);
    }

    if (0 > vehicleSlot > MAX_VEHICLE_ARRAY_SLOT) {
        return false;
    }

    valstr(value, vData[vehicleId][vArray][vehicleSlot]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:teamOnline(const playerid, const argumentIdx, const resultIdx)
{
    new
        arguments[TEXT_FUNCTION_ARGUMENT],
        value[MAX_VALUE_SIZE],
        world = GetPlayerVirtualWorld(playerid),
        onlineCount,
        teamSlot;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", teamSlot)) {
        return false;
    }

    teamSlot--; // Смещение индекса.

    if (0 > teamSlot > MAX_TEAM_SLOT) {
        return false;
    }

    foreach (new targetid : Player) {
        if (GetPlayerVirtualWorld(targetid) != world) {
            continue;
        }

        if (pData[targetid][pTeam] != teamSlot) {
            continue;
        }

        onlineCount++;
    }

	valstr(value, onlineCount);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:online(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        world = GetPlayerVirtualWorld(playerid),
        onlineCount;

    foreach (new targetid : Player)
    {
        if (GetPlayerVirtualWorld(targetid) != world) {
            continue;
        }

        onlineCount++;
    }

    valstr(value, onlineCount);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:anim(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, GetPlayerAnimationIndex(targetid));
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:skin(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, pData[targetid][pSkin]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:acid(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, pData[targetid][pID]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:gun(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, GetPlayerWeapon(targetid));
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:ammo(const playerid, const argumentIdx, const resultIdx)
{
    new
        arguments[TEXT_FUNCTION_ARGUMENT],
        value[MAX_VALUE_SIZE],
        targetid,
        weaponSlot = -1;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dD(-1)", targetid, weaponSlot)) {
        targetid = playerid;
    } else {
        targetid = getTargetIdOrSelf(playerid, targetid);
    }

    if (0 > weaponSlot > PR_MAX_WEAPON_SLOTS) {
        weaponSlot = getGunSlot( GetPlayerWeapon(targetid) );
    }

    valstr(value, dgun[targetid][ammo_slot][weaponSlot]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:vehicle(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, GetPlayerVehicleID(targetid));
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:timestamp(const playerid, const argumentIdx, const resultIdx)
{
    new value[MAX_VALUE_SIZE];

    valstr(value, gettime() - 1577836800);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:team(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, pData[targetid][pTeam] + 1);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:score(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, GetPlayerScore(targetid));
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:money(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, pData[targetid][pMoney]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:health(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    format(value, MAX_VALUE_SIZE, " %.1f", pData[targetid][pHealth]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:armour(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    format(value, MAX_VALUE_SIZE, " %.1f", pData[targetid][pArmour]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:playerid(const playerid, const argumentIdx, const resultIdx)
{
    new value[MAX_VALUE_SIZE];

    valstr(value, playerid);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:name(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    GetPlayerName(targetid, value, MAX_VALUE_SIZE);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:xyz(const playerid, const argumentIdx, const resultIdx)
{
    new
    	Float:x,
	    Float:y,
	    Float:z,
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    GetPlayerPos(targetid, x, y, z);
    format(value, MAX_VALUE_SIZE, "%.1f %.1f %.1f", x, y, z);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:x(const playerid, const argumentIdx, const resultIdx)
{
    new
    	Float:x,
        Float:y,
        Float:z,
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    GetPlayerPos(targetid, x, y, z);
    format(value, MAX_VALUE_SIZE, "%.1f", x);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:y(const playerid, const argumentIdx, const resultIdx)
{
    new
    	Float:x,
        Float:y,
        Float:z,
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    GetPlayerPos(targetid, x, y, z);
    format(value, MAX_VALUE_SIZE, "%.1f", y);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:z(const playerid, const argumentIdx, const resultIdx)
{
    new
    	Float:x,
        Float:y,
        Float:z,
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    GetPlayerPos(targetid, x, y, z);
    format(value, MAX_VALUE_SIZE, "%.1f", z);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:speed(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    if (IsPlayerInAnyVehicle(targetid)) {
        format(value, MAX_VALUE_SIZE, "%d", floatround(Vehicle_Speed(GetPlayerVehicleID(targetid))));
    } else {
	    format(value, MAX_VALUE_SIZE, "%d", floatround(GetPlayerSpeed(targetid)));
    }

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:vehName(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    if (IsPlayerInAnyVehicle(targetid)) {
        ReturnVehicleNameEx(GetPlayerVehicleID(targetid), value);
    } else {
        format(value, MAX_VALUE_SIZE, "N/A");
    }

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:vehModel(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    if (IsPlayerInAnyVehicle(targetid)) {
	    format(value, MAX_VALUE_SIZE, "%d", GetVehicleModel(GetPlayerVehicleID(targetid)));
    } else {
	    format(value, MAX_VALUE_SIZE, "-1");
    }

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:vehHealth(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        Float: health,
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    if (IsPlayerInAnyVehicle(targetid)) {
        GetVehicleHealth(GetPlayerVehicleID(targetid), health);
        format(value, MAX_VALUE_SIZE, "%d", floatround(health));
    } else {
        format(value, MAX_VALUE_SIZE, "-1");
    }

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:gunName(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    GetWeaponName(GetPlayerWeapon(targetid), value);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:time(const playerid, const argumentIdx, const resultIdx)
{
    new
        world = GetPlayerVirtualWorld(playerid),
        value[MAX_VALUE_SIZE];

    valstr(value, VW[world][vTime]);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:weather(const playerid, const argumentIdx, const resultIdx)
{
    new
        world = GetPlayerVirtualWorld(playerid),
        value[MAX_VALUE_SIZE];

    valstr(value, VW[world][vWeather]);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:wanted(const playerid, const argumentIdx, const resultIdx)
{
    new
      value[MAX_VALUE_SIZE],
      targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, GetPlayerWantedLevel(targetid));

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:drunk(const playerid, const argumentIdx, const resultIdx)
{
    new
      value[MAX_VALUE_SIZE],
      targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, GetPlayerDrunkLevel(targetid));

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:channel(const playerid, const argumentIdx, const resultIdx)
{
    new
      value[MAX_VALUE_SIZE],
      targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(value, pData[targetid][pChannel]);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:GetVehModel(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
	arguments[TEXT_FUNCTION_ARGUMENT],
	vehModel;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", vehModel)) {
		return false;
	}

	format(value, MAX_VALUE_SIZE, "%s", ReturnVehicleName(vehModel, 1));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:vehSeat(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

	valstr(value, GetPlayerVehicleSeat(targetid));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:waterlvl(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    new
	Float:depth,
	Float:playerdepth;

	CA_IsPlayerInWater(targetid, depth, playerdepth);
	format(value, MAX_VALUE_SIZE, "%.1f", playerdepth);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:omodel(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
	    world = GetPlayerVirtualWorld(playerid),
        modelid;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

    modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID);
	valstr(value, modelid);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:oxyz(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
        world = GetPlayerVirtualWorld(playerid),
        Float:x,
        Float:y,
        Float:z;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

    GetDynamicObjectPos(objectid, x, y, z);
	format(value, MAX_VALUE_SIZE, "%.2f %.2f %.2f", x, y, z);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:ox(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
	    world,
        Float:x;


	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, x);

	format(value, MAX_VALUE_SIZE, "%.2f", x);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:oy(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
	    world,
        Float:y;


	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, y);

	format(value, MAX_VALUE_SIZE, "%.2f", y);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:oz(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
	    world,
        Float:z;


	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, z);

	format(value, MAX_VALUE_SIZE, "%.2f", z);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:rxyz(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
	    world,
        Float:x,
        Float:y,
        Float:z;

	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_X, x);
	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Y, y);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Z, z);

	format(value, MAX_VALUE_SIZE, "%.2f %.2f %.2f", x, y, z);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:rx(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
	    world,
        Float:x;


	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_X, x);

	format(value, MAX_VALUE_SIZE, "%.2f", x);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:ry(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
	    world,
        Float:y;


	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Y, y);

	format(value, MAX_VALUE_SIZE, "%.2f", y);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:rz(const playerid, const argumentIdx, const resultIdx)
{
    new
    	arguments[TEXT_FUNCTION_ARGUMENT],
    	value[MAX_VALUE_SIZE],
    	objectid,
	    world,
        Float:z;


	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", objectid)) {
		return false;
	}

	objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

	if(objectid <= 0) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Z, z);

	format(value, MAX_VALUE_SIZE, "%.2f", z);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:getDistAction(const playerid, const argumentIdx, const resultIdx)
{
	new
		arguments[TEXT_FUNCTION_ARGUMENT],
		value[MAX_VALUE_SIZE];

	new
		actionId,
		world,
		Float:x, Float:y, Float:z;

	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", actionId)) {
		return false;
	}

	if(!checkValidAction(actionId, world)) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_X, x);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_Y, y);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_Z, z);

	new Float:distance = GetPlayerDistanceFromPoint(playerid, x, y, z);
	format(value, MAX_VALUE_SIZE, "%.2f", distance);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:actionXYZ(const playerid, const argumentIdx, const resultIdx)
{
	new
		arguments[TEXT_FUNCTION_ARGUMENT],
		value[MAX_VALUE_SIZE];

	new
		world,
		actionId,
		Float:x, Float:y, Float:z;

	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", actionId)) {
		return false;
	}

	if(!checkValidAction(actionId, world)) {
		return false;
	}


	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_X, x);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_Y, y);
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_Z, z);


	format(value, MAX_VALUE_SIZE, "%.2f %.2f %.2f", x, y, z);
	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:actionX(const playerid, const argumentIdx, const resultIdx)
{
	new
		arguments[TEXT_FUNCTION_ARGUMENT],
		value[MAX_VALUE_SIZE];

	new
		world,
		actionId,
		Float:x;

	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", actionId)) {
		return false;
	}

	if(!checkValidAction(actionId, world)) {
		return false;
	}


	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_X, x);



	format(value, MAX_VALUE_SIZE, "%.2f", x);
	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:actionY(const playerid, const argumentIdx, const resultIdx)
{
	new
		arguments[TEXT_FUNCTION_ARGUMENT],
		value[MAX_VALUE_SIZE];

	new
		world,
		actionId,
		Float:y;

	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", actionId)) {
		return false;
	}

	if(!checkValidAction(actionId, world)) {
		return false;
	}


	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_Y, y);



	format(value, MAX_VALUE_SIZE, "%.2f", y);
	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:actionZ(const playerid, const argumentIdx, const resultIdx)
{
	new
		arguments[TEXT_FUNCTION_ARGUMENT],
		value[MAX_VALUE_SIZE];

	new
		world,
		actionId,
		Float:z;

	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "d", actionId)) {
		return false;
	}

	if(!checkValidAction(actionId, world)) {
		return false;
	}


	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
		Text3D:worldAction[world][actionId][vAction], E_STREAMER_Z, z);



	format(value, MAX_VALUE_SIZE, "%.2f", z);
	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:zone(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	GetPlayer2DZone(targetid, value, MAX_ZONE_NAME);
	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:getzone(const playerid, const argumentIdx, const resultIdx)
{
	new
		arguments[TEXT_FUNCTION_ARGUMENT],
		value[MAX_VALUE_SIZE];

	new
		Float:x,
		Float:y;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "p<,>ff", x, y)) {
		return false;
	}

	Get2DZone(x, y, value, MAX_ZONE_NAME);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:getzoneid(const playerid, const argumentIdx, const resultIdx)
{
	new
		arguments[TEXT_FUNCTION_ARGUMENT],
		value[MAX_VALUE_SIZE];

	new
		Float:x,
		Float:y;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "p<,>ff", x, y)) {
		return false;
	}

	valstr(value, Get2DZoneId(x, y));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:ping(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	valstr(value, GetPlayerPing(targetid));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:ban(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	if(pData[targetid][pBanned]) {
		valstr(value, 1);
	}
	else {
		valstr(value, 0);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:netstat(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	format(value, MAX_VALUE_SIZE, " %.1f", NetStats_PacketLossPercent(targetid));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:hr(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	format(value, MAX_VALUE_SIZE, "%.1f", (100 * pData[targetid][pHit])/pData[targetid][pShot]);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:fa(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	new
		Float:angle;

	if(IsPlayerInAnyVehicle(targetid)) {
		GetVehicleZAngle(GetPlayerVehicleID(targetid), angle);
	}
	else {
		GetPlayerFacingAngle(targetid, angle);
	}

	format(value, MAX_VALUE_SIZE, "%.1f", angle);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:afk(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);


	valstr(value, pData[targetid][pAFK]);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:death(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);


	valstr(value, pData[targetid][pDeadStage]);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:target(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);


	valstr(value, GetPlayerTargetPlayer(targetid));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:teamName(const playerid, const argumentIdx, const resultIdx)
{
	new
		world,
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	world = GetPlayerVirtualWorld(targetid);


	if(pData[targetid][pTeam] < 0)
	{
		format(value, MAX_VALUE_SIZE, "N/A");
	}
	else
	{
		format(value, MAX_VALUE_SIZE, "%s", worldTeam[world][ pData[targetid][pTeam] ][tName]);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:ext(const playerid, const argumentIdx, const resultIdx)
{
	new
		world,
		arguments[TEXT_FUNCTION_ARGUMENT],
		value[MAX_VALUE_SIZE];

	new
		blockid,
		param;

	world = GetPlayerVirtualWorld(playerid);
	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "p<,>dd", blockid, param)) {
		return false;
	}

	if (blockid < 0 || blockid > VW[world][wMaxCB]) {
		return false;
	}

	switch(param)
	{
		case 1: StreamerBlockGetArray(cmBlock[world][blockid][cbID], 1, value, MAX_VALUE_SIZE);
		case 2: StreamerBlockGetArray(cmBlock[world][blockid][cbID], 2, value, MAX_VALUE_SIZE);
		case 3: StreamerBlockGetArray(cmBlock[world][blockid][cbID], 3, value, MAX_VALUE_SIZE);
		case 4: StreamerBlockGetArray(cmBlock[world][blockid][cbID], 4, value, MAX_VALUE_SIZE);
		case 5: StreamerBlockGetArray(cmBlock[world][blockid][cbID], 5, value, MAX_VALUE_SIZE);
		default: format(value, MAX_VALUE_SIZE, "N/A");
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}


CBF:bodypart(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);


	valstr(value, pData[targetid][pTakeDamageBPart]);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:issuerGun(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);


	valstr(value, pData[targetid][pTakeDamageWeapon]);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:vehColor(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);


	if(IsPlayerInAnyVehicle(targetid))
	{
		new
			color1,
			color2;

		GetVehicleColor(GetPlayerVehicleID(targetid), color1, color2);
		format(value, MAX_VALUE_SIZE, "%s", VehicleColoursTableRGB[color1]);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:vehColor1(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);


	if(IsPlayerInAnyVehicle(targetid))
	{
		new
			color1,
			color2;

		GetVehicleColor(GetPlayerVehicleID(targetid), color1, color2);
		format(value, MAX_VALUE_SIZE, "%d", color1);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:vehColor2(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);


	if(IsPlayerInAnyVehicle(targetid))
	{
		new
			color1,
			color2;

		GetVehicleColor(GetPlayerVehicleID(targetid), color1, color2);
		format(value, MAX_VALUE_SIZE, "%d", color2);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}



CBF:getDistPlayer(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		targetid,
		plid;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "p<,>dD(-1)", plid, targetid)) {
		return false;
	}

	if (!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}

	if (IsPlayerOnline(plid)) {
		valstr(value, floatround(GetPlayerDistanceFromPlayer(targetid, plid)));
	} else {
		valstr(value, 65535);
	}



	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:getDistPos(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		Float:x, Float:y, Float:z,
		targetid;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "p<,>fffD(-1)", x, y, z, targetid)) {
		return false;
	}

	if (!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}

	valstr(value, floatround(GetPlayerDistanceFromPoint(targetid, x, y, z)));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:getDistObject(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		targetid, objectId;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "p<,>dD(-1)", objectId, targetid)) {
		return false;
	}

	if (!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}

	valstr(value, floatround(GetPlayerDistanceFromObject(targetid, objectId)));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:getDistVeh(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		targetid, vehId, world;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "p<,>dD(-1)", vehId, targetid)) {
		return false;
	}

	if (!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}
	world = GetPlayerVirtualWorld(targetid);

	if(vehId < 0 || vehId > MAX_WORLD_VEHICLE) {
		return false;
	}

	valstr(value, floatround(GetPlayerDistanceFromVehicle(targetid, tempWorld[world][vehSlot][vehId])));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:vehPos(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		vehId, world;

	ReadAmxMemoryArray(argumentIdx, arguments);
	world = GetPlayerVirtualWorld(playerid);

	if (sscanf(arguments, "d", vehId)) {
		return false;
	}


	if (!IsValidVehicle(vehId)) {
		return false;
	}

	if(GetVehicleVirtualWorld(vehId) != world) {
		return false;
	}

	new
		Float:x,
		Float:y,
		Float:z;

	GetVehiclePos(vehId, x, y, z);
	format(value, MAX_VALUE_SIZE, "%.1f %.1f %.1f", x, y, z);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:passinfo(const playerid, const argumentIdx, const resultIdx)
{
    new
      value[MAX_VALUE_SIZE],
      targetid = resolveTargetOrSelf(playerid, argumentIdx),
	  world = GetPlayerVirtualWorld(playerid),
      data[2];

    Streamer_GetArrayData(STREAMER_TYPE_PICKUP, pData[targetid][pPickup], E_STREAMER_EXTRA_ID, data);
    pData[targetid][pPickup] = false;

    if (data[1] == 1 && data[0] != -1)
    {
      if (IsPlayerInRangeOfPoint(targetid, 3.0, passData[world][ data[0] ][pExitPosX], passData[world][ data[0] ][pExitPosY], passData[world][ data[0] ][pExitPosZ]))
      {
        valstr(value, data[0]);
      }
    } else if (data[1] != 1 && data[0] != -1) {
      if (IsPlayerInRangeOfPoint(targetid, 3.0, passData[world][ data[0] ][pEnterPosX], passData[world][ data[0] ][pEnterPosY], passData[world][ data[0] ][pEnterPosZ]))
      {
        valstr(value, data[0]);
      }
    } else {
      format(value, MAX_VALUE_SIZE, "-1");
    }

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:nearply(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx),
        int = GetPlayerInterior(targetid),
        world = GetPlayerVirtualWorld(playerid),
        Float: X,
        Float: Y,
        Float: Z,
        lastData[2] = { cellmax, -1 };

    foreach (new i : Player) {
        if (i == targetid) {
            continue;
        }

        if (GetPlayerVirtualWorld(i) != world || GetPlayerInterior(i) != int) {
            continue;
        }

        if (GetPlayerPos(i, X, Y, Z) && (floatround(GetPlayerDistanceFromPoint(targetid, X, Y, Z)) < lastData[0])) {
            lastData[0] = floatround(GetPlayerDistanceFromPoint(targetid, X, Y, Z));
            lastData[1] = i;
        }
    }

    valstr(value, lastData[1]);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:getZ(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		Float:FLOAT_NONE,
		Float:x,
		Float:y,
		Float:z;

	ReadAmxMemoryArray(argumentIdx, arguments);
	if( sscanf(arguments, "p<,>ff", x, y) )
		return false;

	if(!CA_RayCastLine(x, y, 600.0, x, y, -100, FLOAT_NONE, FLOAT_NONE, z))
		z = 0.0;

	format(value, MAX_VALUE_SIZE, "%.1f", z);

   	WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:strlen(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT];

	ReadAmxMemoryArray(argumentIdx, arguments);
	valstr(value, strlen(arguments));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:actorXYZ(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		actorid, Float:aX, Float:aY, Float:aZ,
		world;

	ReadAmxMemoryArray(argumentIdx, arguments);
	world = GetPlayerVirtualWorld(playerid);

	if (sscanf(arguments, "d", actorid)) {
		return false;
	}

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT) {
		return false;
	}

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_X, aX);
	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_Y, aY);
	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_Z, aZ);

	format(value, MAX_VALUE_SIZE, "%.2f %.2f %.2f", aX, aY, aZ);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:actorX(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		actorid, Float:aX,
		world;

	ReadAmxMemoryArray(argumentIdx, arguments);
	world = GetPlayerVirtualWorld(playerid);

	if (sscanf(arguments, "d", actorid)) {
		return false;
	}

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT) {
		return false;
	}

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_X, aX);


	format(value, MAX_VALUE_SIZE, "%.2f", aX);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:actorY(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		actorid, Float:aY,
		world;

	ReadAmxMemoryArray(argumentIdx, arguments);
	world = GetPlayerVirtualWorld(playerid);

	if (sscanf(arguments, "d", actorid)) {
		return false;
	}

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT) {
		return false;
	}

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_Y, aY);


	format(value, MAX_VALUE_SIZE, "%.2f", aY);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:actorZ(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		actorid, Float:aZ,
		world;

	ReadAmxMemoryArray(argumentIdx, arguments);
	world = GetPlayerVirtualWorld(playerid);

	if (sscanf(arguments, "d", actorid)) {
		return false;
	}

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT) {
		return false;
	}

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_Z, aZ);


	format(value, MAX_VALUE_SIZE, "%.2f", aZ);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:getDistActor(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		actorid, Float:aX, Float:aY, Float:aZ,
		world, targetid;

	ReadAmxMemoryArray(argumentIdx, arguments);
	world = GetPlayerVirtualWorld(playerid);

	if (sscanf(arguments, "p<,>dD(-1)", actorid, targetid)) {
		return false;
	}

	if (!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}

	if(actorid < 0 || actorid > MAX_ACTOR_SLOT) {
		return false;
	}

	if(!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
		return false;
	}

	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_X, aX);
	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_Y, aY);
	Streamer_GetFloatData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_Z, aZ);

	valstr(value, floatround(GetPlayerDistanceFromPoint(targetid, aX, aY, aZ)));

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:retval(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		retvalId, targetid;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if (sscanf(arguments, "p<,>dD(-1)", retvalId, targetid)) {
		return false;
	}

	if (!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}

	if(retvalId < 0 || retvalId > 9) {
		return false;
	}

	valstr(value, pData[targetid][pRetVal][retvalId]);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:retstr(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		retvalId, targetid;

	ReadAmxMemoryArray(argumentIdx, arguments);

	sscanf(arguments, "p<,>D(-1)D(-1)", retvalId, targetid);

	if (!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}


	if (retvalId == -1)
	{
		format(value, MAX_VALUE_SIZE, "%s", pData[targetid][pRetStr]);
	}
	else
	{
		if(retvalId < 0 || retvalId > 9) {
			return false;
		}

		format(value, MAX_VALUE_SIZE, "%.24s", pData[targetid][pRetStr][ retvalId * 24 ]);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:getDist(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT];

	new
		Float: firstX,
		Float: firstY,
		Float: firstZ,
		Float: secondX,
        Float: secondY,
		Float: secondZ;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "p<,>ffffff", firstX, firstY, firstZ, secondX, secondY, secondZ)) {
		return false;
	}

	format(value, MAX_VALUE_SIZE, "%.2f", VectorSize(firstX - secondX, firstY - secondY, firstZ - secondZ) );

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:attach(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		attachId, targetid;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "p<,>dD(-1)", attachId, targetid)) {
			return false;
	}

	if(attachId < 1 || attachId > 10) {
			return false;
	}

	attachId--;

	if(!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}

	valstr(value, pAttach[targetid][attachId][0]);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:attachModel(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		attachId, targetid;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "p<,>dD(-1)", attachId, targetid)) {
			return false;
	}

	if(attachId < 1 || attachId > 10) {
			return false;
	}

	attachId--;

	if(!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}

	valstr(value, pAttach[targetid][attachId][1]);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:isAttachModel(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT],
		modelId, targetid, attachId;

	ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arguments, "p<,>dD(-1)", modelId, targetid)) {
		return false;
	}

	if(!IsPlayerOnline(targetid)) {
		targetid = playerid;
	}

	attachId = -1;
	for(new i; i < 10; i++)
	{
		if(pAttach[targetid][i][1] == modelId) {
			attachId = i + 1;
			break;
		}
	}

	valstr(value, attachId);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:randomPlayer(const playerid, const argumentIdx, const resultIdx)
{
	new
		world,
		value[MAX_VALUE_SIZE],
		arguments[TEXT_FUNCTION_ARGUMENT];

	ReadAmxMemoryArray(argumentIdx, arguments);
	world = GetPlayerVirtualWorld(playerid);

	new
		category[24],
		categoryType,
		type[2],
		playerCount = -1,
		playerList[500];

	sscanf(arguments, "p<,>s[24]D(0)D(0)", category, type[0], type[1]);

	if(!isnull(category))
	{
		if(!strcmp(category, "team", true))
		{
			type[0]--;
			categoryType = 1;
		}
		else if(!strcmp(category, "skin", true))
			categoryType = 2;
		else if(!strcmp(category, "veh", true))
			categoryType = 3;
		else if(!strcmp(category, "data", true))
			categoryType = 4;
		else if(!strcmp(category, "wanted", true))
			categoryType = 5;
		else if(!strcmp(category, "action", true))
			categoryType = 6;
		else if(!strcmp(category, "dead", true))
			categoryType = 7;
		else if(!strcmp(category, "alive", true))
			categoryType = 8;
	}

	foreach(new player : Player)
	{
		if(GetPlayerVirtualWorld(player) != world)
			continue;

		if(categoryType != 0)
		{
			if(categoryType == 1)
			{
				if(pData[player][pTeam] != type[0])
					continue;
			}
			else if(categoryType == 2)
			{
				if(pData[player][pSkin] != type[0])
						continue;
			}
			else if(categoryType == 3)
			{
				if(GetVehicleModel(GetPlayerVehicleID(player)) != type[0])
					continue;
			}
			else if(categoryType == 4)
			{
				if(type[0] < 0 || type[0] > 26)
					continue;

				if(pData[player][cbData][ type[0] ] != type[1])
					continue;
			}
			else if(categoryType == 5)
			{
				if(GetPlayerWantedLevel(player) != type[0])
					continue;
			}
			else if(categoryType == 6)
			{
				if(GetPlayerSpecialAction(player) != type[0])
					continue;
			}
			else if(categoryType == 7)
			{
				if(!pData[player][pDead])
					continue;
			}
			else if(categoryType == 8)
			{
				if(pData[player][pDead])
					continue;
			}
		}

		playerCount++;
		playerList[playerCount] = player;
	}

	if(playerCount != -1)
		valstr(value, playerList[ RandomEx(0, playerCount) ]);
	else
		valstr(value, 0);

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}


CBF:moder(const playerid, const argumentIdx, const resultIdx)
{
	new
		world,
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	world = GetPlayerVirtualWorld(targetid);
	valstr(value, pData[targetid][pModer]);

	if (GetWorldOwner(targetid, world)) {
		valstr(value, 6);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:specState(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

	if (pData[targetid][pInSpec]) {
		valstr(value, 1);
	} else {
		valstr(value, 0);
	}

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:specTarget(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

	if (!pData[targetid][pInSpec]) {
		format(value, MAX_VALUE_SIZE, "N/A");
	} else {
		valstr(value, pData[targetid][pSpectator]);
	}

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:int(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

	valstr(value, pData[targetid][pInterior]);

    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:vip(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	if (pData[targetid][vip] == 0) {
		valstr(value, 0);
	} else if (pData[targetid][vip] > 0) {
		valstr(value, 1);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:raycast(const playerid, const argumentIdx, const resultIdx)
{
	new
		value[MAX_VALUE_SIZE],
		Float:pX, Float:pY, Float:pZ,
		Float:vX, Float:vY, Float:vZ,
		Float:atX, Float:atY, Float:atZ,
		arguments[TEXT_FUNCTION_ARGUMENT],
		category[24],
		Float: dist,
		col,
		coord[4] = "xyz";

	ReadAmxMemoryArray(argumentIdx, arguments);

	sscanf(arguments, "s[24]D(30)D(0)s[4]", category, dist, col, coord);

	if (!strcmp(category, "cam", true)) {
		GetPlayerCameraPos(playerid, pX, pY, pZ);
		GetPlayerCameraFrontVector(playerid, vX, vY, vZ);

		vX = pX + (vX * dist);
		vY = pY + (vY * dist);
		vZ = pZ + (vZ * dist);

		CA_RayCastLine(pX, pY, pZ, vX, vY, vZ, atX, atY, atZ);
	} else if (!strcmp(category, "pos", true)) {
		if (IsPlayerInAnyVehicle(playerid)) {
			GetVehiclePos(GetPlayerVehicleID(playerid), pX, pY, pZ);
			GetVehicleRotation(GetPlayerVehicleID(playerid), vX, vY, vZ);

			GetPlayerPos(playerid,  pX, pY, pZ);
			GetPlayerFacingAngle(playerid, vZ);

			vX = pX + (dist * floatsin(-vZ, degrees));
			vY = pY + (dist * floatcos(-vZ, degrees));
			vZ = pZ + (dist * floatsin(vX, degrees));

			CA_RayCastLine(pX, pY, pZ, vX, vY, pZ, atX, atY, atZ);
		} else {
			GetPlayerPos(playerid,  pX, pY, pZ);
			GetPlayerFacingAngle(playerid, vZ);

			vX = pX + (dist * floatsin(-vZ, degrees));
			vY = pY + (dist * floatcos(-vZ, degrees));

			CA_RayCastLine(pX, pY, pZ, vX, vY, pZ, atX, atY, atZ);
		}
	}

	if (col) {
		if (atX == 0.0 && atY == 0.0 && atZ == 0.0) {
			format(value, MAX_VALUE_SIZE, "%.1f %1.f %1.f", vX, vY, vZ);
		} else {
			format(value, MAX_VALUE_SIZE, "%.1f %.1f %.1f", atX, atY, atZ);
		}
	} else {
		format(value, MAX_VALUE_SIZE, "%.1f %.1f %.1f", atX, atY, atZ);
	}

	if (!strcmp(coord, "xyz")) {
		return false;
	}

	new Float:cX, Float:cY, Float:cZ;

	if (sscanf(value, "fff", cX, cY, cZ)) {
		return false;
	}

	if (!strcmp(coord, "x")) {
		format(value, MAX_VALUE_SIZE, "%1.f", cX);
	} else if (!strcmp(coord, "y")) {
		format(value, MAX_VALUE_SIZE, "%1.f", cY);
	} else if (!strcmp(coord, "z")) {
		format(value, MAX_VALUE_SIZE, "%1.f", cZ);
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}


 CBF:chatStyle(const playerid, const argumentIdx, const resultIdx) {
 	new
 		value[MAX_VALUE_SIZE],
 		targetid = resolveTargetOrSelf(playerid, argumentIdx);

 	valstr(value, pData[targetid][pChatStyle]);

 	WriteAmxMemoryArray(resultIdx, value);
 	return true;
 }

 CBF:freeze(const playerid, const argumentIdx, const resultIdx) {
 	new
 		value[MAX_VALUE_SIZE],
 		targetid = resolveTargetOrSelf(playerid, argumentIdx);

 	if (pData[targetid][Frozen]) {
 		valstr(value, 1);
 	} else {
 		valstr(value, 0);
 	}

 	WriteAmxMemoryArray(resultIdx, value);
 	return true;
 }

 CBF:freezeTime(const playerid, const argumentIdx, const resultIdx) {
 	new
 		value[MAX_VALUE_SIZE],
 		targetid = resolveTargetOrSelf(playerid, argumentIdx);

 	valstr(value, pData[targetid][pFreezeTime]);

 	WriteAmxMemoryArray(resultIdx, value);
 	return true;
 }

 CBF:gm(const playerid, const argumentIdx, const resultIdx) {
 	new
 		value[MAX_VALUE_SIZE],
 		targetid = resolveTargetOrSelf(playerid, argumentIdx);

 	if (pData[targetid][GM]) {
 		valstr(value, 1);
 	} else {
 		valstr(value, 0);
 	}

 	WriteAmxMemoryArray(resultIdx, value);
 	return true;
 }

 CBF:mute(const playerid, const argumentIdx, const resultIdx) {
 	new
 		value[MAX_VALUE_SIZE],
 		targetid = resolveTargetOrSelf(playerid, argumentIdx),
 		time = pData[targetid][pWorldMute] - gettime();

 	if (time > 0) {
 		valstr(value, 1);
 	} else {
 		valstr(value, 0);
 	}

 	WriteAmxMemoryArray(resultIdx, value);
 	return true;
 }

 CBF:muteTime(const playerid, const argumentIdx, const resultIdx) {
 	new
 		value[MAX_VALUE_SIZE],
 		targetid = resolveTargetOrSelf(playerid, argumentIdx),
 		time = pData[targetid][pWorldMute] - gettime();

 	valstr(value, time);

 	WriteAmxMemoryArray(resultIdx, value);
 	return true;
 }

CBF:taser(const playerid, const argumentIdx, const resultIdx) {
	 new
		 value[MAX_VALUE_SIZE],
		 targetid = resolveTargetOrSelf(playerid, argumentIdx);
		
	 if (pData[targetid][pTazer]) {
		valstr(value, "1");
	 } else {
	 	valstr(value, "0");
	 }
		
	 WriteAmxMemoryArray(resultIdx, value);
	 return true;
}

CBF:lastActor(const playerid, const argumentIdx, const resultIdx) {
	 new
		 value[MAX_VALUE_SIZE],
		 targetid = resolveTargetOrSelf(playerid, argumentIdx);
		
	 valstr(value, pData[targetid][pActor]);
		
	 WriteAmxMemoryArray(resultIdx, value);
	 return true;
}

CBF:clist(const playerid, const argumentIdx, const resultIdx) {
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);

	valstr(value, GetPlayerColor(targetid));
	
	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:fightStyle(const playerid, const argumentIdx, const resultIdx) {
	new
		value[MAX_VALUE_SIZE],
		targetid = resolveTargetOrSelf(playerid, argumentIdx);
	
	if (GetPlayerFightingStyle(targetid) == FIGHT_STYLE_NORMAL) {
		valstr(value, "1");
	} else if (GetPlayerFightingStyle(targetid) == FIGHT_STYLE_BOXING) {
		valstr(value, "2");
	} else if (GetPlayerFightingStyle(targetid) == FIGHT_STYLE_KUNGFU) {
		valstr(value, "3");
	} else if (GetPlayerFightingStyle(targetid) == FIGHT_STYLE_KNEEHEAD) {
		valstr(value, "4");
	} else if (GetPlayerFightingStyle(targetid) == FIGHT_STYLE_GRABKICK) {
		valstr(value, "5");
	} else if (GetPlayerFightingStyle(targetid) == FIGHT_STYLE_ELBOW) {
		valstr(value, "6");
	}

	WriteAmxMemoryArray(resultIdx, value);
	return true;
}
