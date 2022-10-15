/**
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
        varData[MAX_VAR_DATA_LEN];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "s[32]", varData)) {
        return false;
    }

    if (getVarData(playerid, varData, value) == INVALID_VECTOR_INDEX) {
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
        varData[MAX_VAR_DATA_LEN];

    ReadAmxMemoryArray(argumentIdx, arguments);

	if(sscanf(arg, "p<,>s[32]d", varData, targetid)) {
        targetid = playerid;
    }

    if (!IsPlayerOnline(targetid)) {
        return false;
    }

    if (sscanf(arguments, "s[32]", varData)) {
        return false;
    }

    if (getPlayerVarData(targetid, varData, value) == INVALID_VECTOR_INDEX) {
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

	if (sscanf(arg, "dd", vehicleId, vehicleSlot)) {
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
        value[MAX_VALUE_SIZE],
        targetid,
        weaponSlot = -1;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arg, "dD(-1)", targetid, weaponSlot)) {
        targetid = playerid;
    } else {
        targetid = getTargetIdOrSelf(playerid, targetid);
    }

    if (0 > weaponSlot > PR_MAX_WEAPON_SLOTS) {
        weaponSlot = getGunSlot( GetPlayerWeapon(targetid) );
    }

    valstr(str, dgun[targetid][ammo_slot][weaponSlot]);
    WriteAmxMemoryArray(resultIdx, value);
    return true;
}

CBF:vehicle(const playerid, const argumentIdx, const resultIdx)
{
    new
        value[MAX_VALUE_SIZE],
        targetid = resolveTargetOrSelf(playerid, argumentIdx);

    valstr(str, GetPlayerVehicleID(targetid));
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

CBF:health(const playerid, const argumentIdx, const resultIdx)
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
		Float:z;
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
		Float:z;
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
		Float:z;
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
		Float:z;
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

	if (IsPlayerInAnyVehicle(userid)) {
        format(value, MAX_VALUE_SIZE, "%d", floatround(Vehicle_Speed(GetPlayerVehicleID(targetid))));
    } else {
		format(value, MAX_VALUE_SIZE, "%d", floatround(GetPlayerSpeed(userid)));
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

	if(IsPlayerInAnyVehicle(targetid)) {
		format(value, MAX_VALUE_SIZE, GetVehicleModel(GetPlayerVehicleID(targetid)));
	} else {
		format(value, MAX_VALUE_SIZE, "-1");
	}

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
    	value[MAX_VALUE_SIZE],
    	objectid,
	world,
        modelid;


	world = GetPlayerVirtualWorld(playerid);
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

        GetDynamicObjectPos(objectid, x, y, z);
	format(value, MAX_VALUE_SIZE, "%.2f %.2f %.2f", x, y, z);
	
	WriteAmxMemoryArray(resultIdx, value);
	return true;
}

CBF:ox(const playerid, const argumentIdx, const resultIdx)
{
    new 
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

CBF:ox(const playerid, const argumentIdx, const resultIdx)
{
    new 
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
