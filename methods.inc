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

CB:addHealth(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: hp,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "f", hp))
        return SendMissCBMessage(playerid, blockid, actionid, "health");

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerHealth(playerid, pData[playerid][pHealth] + hp);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
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

CB:addArmor(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: arm,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "f", arm))
        return SendMissCBMessage(playerid, blockid, actionid, "armour");

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerHealth(playerid, pData[playerid][pArmour] + arm);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerHealth(targetid, pData[targetid][pArmour] + arm);
    }
    return true;
}

CB:setPos(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: x,
    Float: y,
    Float: z,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "fff", x, y, z))
        return SendMissCBMessage(playerid, blockid, actionid, "x y z");

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerPos(playerid, x, y, z);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerPos(targetid, x, y, z);
    }
    return true;
}

CB:setSkin(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new skin,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", skin))
        return SendMissCBMessage(playerid, blockid, actionid, "skin");

    if (0 > skin > 311)
        return SendErrorCBMessage(playerid, blockid, actionid, "skin", "0-311");

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerSkin(playerid, skin);
        pData[playerid][pSkin] = skin;
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerSkin(targetid, skin);
        pData[targetid][pSkin] = skin;
    }
    return true;
}

CB:setTime(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new time,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", time))
        return SendMissCBMessage(playerid, blockid, actionid, "time");

    if (0 > time > 24)
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

CB:setWeather(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new weather,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", weather))
        return SendMissCBMessage(playerid, blockid, actionid, "weather");

    if (0 > weather > 255)
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

CB:EditAction(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        slot,
        str[144];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "ds[144]", slot, str)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actionid str");
    }

    if (slot < 0 || slot > MAX_WORLD_ACTION) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actionid", "0+");
    }

    if (Text3D:worldAction[world][slot][vAction] == Text3D:INVALID_3DTEXT_ID) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actionid", "valid_action");
    }

    new numStart;
    while (numStart != -1) {
        numStart = strfind(str, "@", true);
        if (numStart == -1) {
            break;
        }

        strdel(str, numStart, numStart + 1);
        strins(str, "\n", numStart, 144);
    }

    UpdateDynamic3DTextLabelText(worldAction[world][slot][vAction], COLOR_PURPLE, str);
    return true;
}

CB:DelAction(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        slot;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", slot)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actionid");
    }

    if (slot < 0 || slot > MAX_WORLD_ACTION) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actionid", "0+");
    }

    if (Text3D:worldAction[world][slot][vAction] == Text3D:INVALID_3DTEXT_ID) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actionid", "valid_action");
    }

    DestroyDynamic3DTextLabel(worldAction[world][slot][vAction]);

    return true;
}

CB:MoveAction(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        Float:x,
        Float:y,
        Float:z,
        slot;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dfff", slot, x, y, z)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actionid x y z");
    }

    if (slot < 0 || slot > MAX_WORLD_ACTION) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actionid", "0+");
    }

    if (Text3D:worldAction[world][slot][vAction] == Text3D:INVALID_3DTEXT_ID) {
        return CBWrongData(playerid, blockid, world);
    }

    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, worldAction[world][slot][vAction], E_STREAMER_X, x);
    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, worldAction[world][slot][vAction], E_STREAMER_Y, y);
    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, worldAction[world][slot][vAction], E_STREAMER_Z, z);

    return true;
}

CB:FreezePlayer(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        time;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", time)) {
        return SendMissCBMessage(playerid, blockid, actionid, "time");
    }

    if (time < -1 || time > 10000) {
        return SendErrorCBMessage(playerid, blockid, actionid, "time", "-1 - 10000");
    }

    if (cmBlock[world][blockid][cbMode]) {
        if (time == -1) {
            TogglePlayerControllable(playerid, 0);
        } else {
            ToFreeze(playerid, time);
        }

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (time == -1) {
            TogglePlayerControllable(targetid, 0);
        } else {
            ToFreeze(targetid, time);
        }
    }

    return true;
}

CB:SetSkill(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        type,
        skill;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dd", type, skill)) {
        return SendMissCBMessage(playerid, blockid, actionid, "type skill");
    }

    if (skill < 0 || skill > 999) {
        return SendErrorCBMessage(playerid, blockid, actionid, "skill", "0-999");
    }

    if (type < 0 || type > 10) {
        return SendErrorCBMessage(playerid, blockid, actionid, "type", "0-10");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        SetPlayerSkillLevel(playerid, type, skill);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerSkillLevel(targetid, type, skill);
    }

    return true;
}

CB:SetStyle(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        type;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", type)) {
        return SendMissCBMessage(playerid, blockid, actionid, "type");
    }

    if (type < 1 || type > 6) {
        return SendErrorCBMessage(playerid, blockid, actionid, "type", "1-6");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        switch (type) {
            case 1 : pData[playerid][pStyle] = 4;
            case 2 : pData[playerid][pStyle] = 5;
            case 3 : pData[playerid][pStyle] = 6;
            case 4 : pData[playerid][pStyle] = 7;
            case 5 : pData[playerid][pStyle] = 15;
            case 6 : pData[playerid][pStyle] = 16;
        }

        FightStyle(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(playerid, blockid, world)) {
            continue;
        }

        switch (type) {
            case 1 : pData[targetid][pStyle] = 4;
            case 2 : pData[targetid][pStyle] = 5;
            case 3 : pData[targetid][pStyle] = 6;
            case 4 : pData[targetid][pStyle] = 7;
            case 5 : pData[targetid][pStyle] = 15;
            case 6 : pData[targetid][pStyle] = 16;
        }

        FightStyle(targetid);
    }

    return true;
}

CB:KickPlayer(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {

        SetPlayerVw(playerid, 0);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerVw(targetid, 0);
    }

    return true;
}

CB:BubblePlayer(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        text[128],
        time;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "ds[128]", time, text)) {
        return SendMissCBMessage(playerid, blockid, actionid, "time<ms> text");
    }

    if (time < 100 || time > 10000) {
        return SendErrorCBMessage(playerid, blockid, actionid, "time", "100-10000");
    }

    if (!cmBlock[world][blockid][cbMode]) {


        SetPlayerChatBubble(playerid, text, 0xFFFFFFFF, 10.0, time);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerChatBubble(targetid, text, 0xFFFFFFFF, 10.0, time);
    }

    return true;
}

CB:HideObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", objectid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
    if (objectid <= 0) {
        return SendErrorCBMessage(playerid, blockid, actionid, "objectid", "1+");
    }

    Streamer_ToggleItem(-1, STREAMER_TYPE_OBJECT, objectid, 0);
    Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
    return true;
}

CB:ShowObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", objectid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
    if (objectid <= 0) {
        return SendErrorCBMessage(playerid, blockid, actionid, "objectid", "1+");
    }

    Streamer_ToggleItem(-1, STREAMER_TYPE_OBJECT, objectid, 1);
    Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
    return true;
}

CB:WipeVehicle(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    worldWipeFreeVeh(world);
    return true;
}

CB:SpawnVehicle(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    worldSpawnFreeVeh(world);
    return true;
}

CB:SetGravity(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        Float:worldGravity;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "f", worldGravity)) {
        return SendMissCBMessage(playerid, blockid, actionid, "worldGravity");
    }

    if (worldGravity > 0.1 || worldGravity < 0.00001) {
        return SendErrorCBMessage(playerid, blockid, actionid, "worldGravity", "0.1-0.00001");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        SetPlayerGravity(playerid, worldGravity);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            return false;
        }

        SetPlayerGravity(targetid, worldGravity);
    }

    return true;
}

CB:GiveDamage(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        Float:damage;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "f", damage)) {
        return SendMissCBMessage(playerid, blockid, actionid, "damage");
    }

    if (damage < 0.1 || damage > 9999.0) {
        return SendErrorCBMessage(playerid, blockid, actionid, "damage", "0.1-9999.0");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        AntiCheatGetHealth(playerid, pData[playerid][pHealth]);
        AntiCheatGetArmour(playerid, pData[playerid][pArmour]);

        if (pData[playerid][pArmour] > 0.0) {
            pData[playerid][pArmour] = (pData[playerid][pArmour] - damage);

            if (pData[playerid][pArmour] > 0.0) {
                SetPlayerArmour(playerid, pData[playerid][pArmour]);
            } else {
                SetPlayerArmour(playerid, 0);
                SetPlayerHealth(playerid, pData[playerid][pHealth] + pData[playerid][pArmour]);
            }

        } else {
            pData[playerid][pHealth] = (pData[playerid][pHealth] - damage);

            if (pData[playerid][pHealth] <= 0.9) {
                SetPlayerHealth(playerid, 0.0);
            } else {
                SetPlayerHealth(playerid, pData[playerid][pHealth]);
            }
        }

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(playerid, blockid, world)) {
            continue;
        }

        AntiCheatGetHealth(targetid, pData[targetid][pHealth]);
        AntiCheatGetArmour(targetid, pData[targetid][pArmour]);

        if (pData[targetid][pArmour] > 0.0) {
            pData[targetid][pArmour] = (pData[targetid][pArmour] - damage);

            if (pData[targetid][pArmour] > 0.0) {
                SetPlayerArmour(targetid, pData[targetid][pArmour]);
            } else {
                SetPlayerArmour(targetid, 0);
                SetPlayerHealth(targetid, pData[targetid][pHealth] + pData[targetid][pArmour]);
            }

        } else {
            pData[targetid][pHealth] = (pData[targetid][pHealth] - damage);

            if (pData[targetid][pHealth] <= 0.9) {
                SetPlayerHealth(targetid, 0.0);
            } else {
                SetPlayerHealth(targetid, pData[targetid][pHealth]);
            }
        }
    }

    return true;
}

CB:SetDrunk(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        drunkLvl;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", drunkLvl)) {
        return SendMissCBMessage(playerid, blockid, actionid, "drunkLvl");
    }

    if (drunkLvl < 0 || drunkLvl > 50000) {
        return SendErrorCBMessage(playerid, blockid, actionid, "drunkLvl", "0-50000")
    }

    if (!cmBlock[world][blockid][cbMode]) {


        SetPlayerDrunkLevel(playerid, drunkLvl);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(playerid, blockid, world)) {
            continue;
        }

        SetPlayerDrunkLevel(targetid, drunkLvl);
    }

    return true;
}

CB:EditCallSign(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        str[144];

    ReadAmxMemoryArray(argumentIdx, str);

    if (sscanf(arguments, "s[144]", str)) {
        return SendMissCBMessage(playerid, blockid, actionid, "str");
    }

    new numStart;
    while (numStart != -1) {
        numStart = strfind(str, "@", true);
        if (numStart == -1) {
            break;
        }

        strdel(str, numStart, numStart + 1);
        strins(str, "\n", numStart, 144);
    }

    if (!cmBlock[world][blockid][cbMode]) {

        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        new
        Float:x,
        Float:y,
        Float:z,
        vehicleid = GetPlayerVehicleID(playerid);


        if (CallsignID[vehicleid] == Text3D:INVALID_3DTEXT_ID) {
            if (isBike(GetVehicleModel(vehicleid))) {
                x = -0.2;
                y = -1.2;
                z = 0.3;
            } else {
                x = -1;
                y = -2.8;
                z = -0.2;
            }

            CallsignID[vehicleid] = CreateDynamic3DTextLabel(str, COLOR_WHITE, x, y, z, 30.0, INVALID_PLAYER_ID, vehicleid, 0, world, -1, -1, -1);
        } else {
            UpdateDynamic3DTextLabelText(CallsignID[vehicleid], COLOR_WHITE, str);
        }

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        new
        Float:x,
        Float:y,
        Float:z,
        vehicleid = GetPlayerVehicleID(targetid);


        if (CallsignID[vehicleid] == Text3D:INVALID_3DTEXT_ID) {
            if (isBike(GetVehicleModel(vehicleid))) {
                x = -0.2;
                y = -1.2;
                z = 0.3;
            } else {
                x = -1;
                y = -2.8;
                z = -0.2;
            }

            CallsignID[vehicleid] = CreateDynamic3DTextLabel(str, COLOR_WHITE, x, y, z, 30.0, INVALID_PLAYER_ID, vehicleid, 0, world, -1, -1, -1);
        } else {
            UpdateDynamic3DTextLabelText(CallsignID[vehicleid], COLOR_WHITE, str);
        }
    }

    return true;
}

CB:CallBlock(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        retval[3],
        userid,
        callBlock;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dD(-1)D(0)D(0)D(0)", callBlock, userid, retval[0], retval[1], retval[2])) {
        return SendMissCBMessage(playerid, blockid, actionid, "blockid *userid *retval0 *retval1 *retval2");
    }

    if (callBlock < 0 || callBlock > VW[world][wMaxCB]) {
        return SendErrorCBMessage(playerid, blockid, actionid, "blockid", "1+");
    }

    if (userid < 0 || userid > MAX_PLAYERS) {
        userid = playerid;
    }

    if (!cbCompareMode(userid, blockid, world)) {
        return false;
    }

    pData[userid][pRetStr] = EOS;
    GetPlayerName(playerid, pData[userid][pRetStr][0], 24);

    pData[userid][pRetVal][0] = playerid;

    if (retval[0] != 0) {
        pData[userid][pRetVal][1] = retval[0];
    }

    if (retval[1] != 0) {
        pData[userid][pRetVal][2] = retval[1];
    }

    if (retval[2] != 0) {
        pData[userid][pRetVal][3] = retval[2];
    }

    pData[userid][pRetVal][4] = false;
    pData[userid][pRetVal][5] = false;
    pData[userid][pRetVal][6] = false;
    pData[userid][pRetVal][7] = false;
    pData[userid][pRetVal][8] = false;
    pData[userid][pRetVal][9] = false;

    OnCmBlockHandler(userid, callBlock, world, -1);
    return true;
}

CB:ObjectSetText(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    argumets[TEXT_FUNCTION_ARGUMENT],
        objectid,
        slotid,
        str[144];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dds[144]", objectid, slot, str)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid slot str");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
    if (objectid <= 0) {
        return false;
    }

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

    while (numStart != -1) {
        numStart = strfind(str, "@", true);
        if (numStart == -1) {
            break;
        }

        strdel(str, numStart, numStart + 1);
        strins(str, "\n", numStart, 144);
    }

    GetDynamicObjectMaterialText(objectid, slotid, text, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
    SetDynamicObjectMaterialText(objectid, slotid, str, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment);
    return true;
}

CB:ObjectSetColor(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid,
        slotid,
        color;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "ddx", objectid, slotid, color)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid slotid color<0xAARRGGBB>");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
    if (objectid <= 0) {
        return false;
    }

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

CB:CloneObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid,
        modelid,
        Float:x,
        Float:y,
        Float:z,
        Float:rx,
        Float:rz,
        Float:ry;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dF(0.0)F(0.0)F(0.0)", objectid, x, y, z)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objecitd x y z *rx* ry *rz");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
    if (objectid <= 0)
        return false;

    modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID);

    if (x == 0.0 && y == 0.0 && z == 0.0) {
        GetDynamicObjectPos(objectid, x, y, z);
    }

    GetDynamicObjectRot(objectid, rx, ry, rz);

    new tempObject = addTempWorld(modelid, x, y, z, rx, ry, rz, world);

    if (tempObject == -1) {
        return true;
    }

    new cloneObject = VECTOR_get_val(WorldObjectSystem[world][wosObject], tempObject);

    for (new i; i < TEXTURE_SLOT; i++) {
        if (!IsDynamicObjectMaterialUsed(objectid, i)) {
            continue;
        }

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

CB:CreateObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid,
        modelid,
        Float:x,
        Float:y,
        Float:z,
        Float:rx,
        Float:ry,
        Float:rz;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dfffF(0.0)F(0.0)F(0.0)", modelid, x, y, z, rx, ry, rz)) {
        return SendMissCBMessage(playerid, blockid, actionid, "modelid x y z *rx *ry *rz");
    }

    switch (modelid) {
        case 1382, 1385, 1379, 1383, 5126, 1395, 2983, 2917, 3474, 1376, 1393, 1377, 1391, 1390, 1389, 1388, 1387, 1386, 1384, 1381, 1380, 1378, 1392 : return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "valid_model");
        case 1524..1531 : return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "valid_model");
        case 1225 : return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "valid_model");
    }

    objectid = addTempWorld(modelid, x, y, z, rx, ry, rz, world);

    if (objectid == -1) {
        return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "valid_model");
    }

    pData[playerid][pRetVal][0] = objectid;

    return true;
}

CB:SetTexture(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid,
        slot,
        texture;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "ddd", objectid, slot, texture)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid slot texture");
    }

    if (slot < 0 || slot > TEXTURE SLOT) {
        return SendErrorCBMessage(playerid, blockid, actionid, "slot", "0-16");
    }

    if (texture < 0 || texture > MAX_TEXTURES) {
        return SendErrorCBMessage(playerid, blockid, actionid, "texture", "0+");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
    if (objectid <= 0) {
        return false;
    }

    TG_SetDynamicObjectMaterial(
        objectid,
        slot,
        ObjectTextures[texture][TModel],
        ObjectTextures[texture][TXDName],
        ObjectTextures[texture][TextureName],
        0);

    return true;
}

CB:DelObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        slot,
        objectid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", slot)) {
        return SendMissCBMessage(playerid, blockid, actionid, "id");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], slot);
    if (objectid <= 0) {
        return false;
    }

    DestroyDynamicObject(objectid);
    remTempWorld(world, slot);
    worldUpdateStreamer(world, STREAMER_TYPE_OBJECT);

    return true;
}

CB:MoveObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid,
        Float:x,
        Float:y,
        Float:z,
        Float:rx,
        Float:rz,
        Float:ry,
        Float:speed;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dfffF(0.0)F(0.0)F(0.0)F(0.0)", objectid, x, y, z, speed, rx, ry, rz)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid x y z *speed *rx *ry *rz")
    }

    if (speed < 0.0 || speed > 50.0) {
        return false;
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

    if (objectid <= 0) {
        return false;
    }

    if (speed == 0.0) {
        SetDynamicObjectPos(objectid, x, y, z);
    } else {
        MoveDynamicObject(objectid, x, y, z, speed, rx, ry, rz);
    }

    return true;
}

CB:setVehCollision(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        status;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", status)) {
        return SendMissCBMessage(playerid, blockid, actionid, "status");
    }

    if (status != 0 && status != 1) {
        return SendErrorCBMessage(playerid, blockid, actionid, "status", "0/1");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        DisableRemoteVehicleCollisions(playerid, status);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        DisableRemoteVehicleCollisions(targetid, status);
    }

    return true;
}

CB:playStream(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        url[144];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "s[144]", url)) {
        return SendMissCBMessage(playerid, blockid, actionid, "url");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        PlayAudioStreamForPlayer(playerid, url);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        PlayAudioStreamForPlayer(targetid, url);
    }

    return true;
}

CB:SetModelObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid,
        modelid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dd", objectid, modeld)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid modelid");
    }

    if (!IsIDEValid(modelid)) {
        return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "valid_model");
    }

    switch (modelid) {
        case 1382, 1385, 1379, 1383, 5126, 1395, 2983, 2917, 3474, 1376, 1393, 1377, 1391, 1390, 1389, 1388, 1387, 1386, 1384, 1381, 1380, 1378, 1392 : return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "valid_model");
        case 1524..1531 : return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "valid_model");
        case 1225 : return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "valid_model");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

    if (objectid <= 0) {
        return SendErrorCBMessage(playerid, blockid, actionid, "modelid", "1+");
    }

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID, modelid);
    Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

    return true;
}

CB:SelectObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {
        SelectObject(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SelectObject(targetid);
    }

    return true;
}

CB:EditObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", objectid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "ojectid");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);

    if (objectid < 0) {
        return SendErrorCBMessage(playerid, blockid, actionid, "objectid", "objectid>0");
    }

    EditDynamicObject(playerid, objectid);

    return true;
}

CB:CancelEdit(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {

        CancelEdit(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        CancelEdit(targetid);
    }

    return true;
}

CB:Create3DText(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        actText[144],
        Float:x,
        Float:y,
        Float:z;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "fffs[144]", x, y, z, actText)) {
        return SendMissCBMessage(playerid, blockid, actionid, "x y z text");
    }

    for (new i; i < MAX_WORLD_ACTION; i++) {
        if (Text3D:worldAction[world][i][vAction] != Text3D:INVALID_3DTEXT_ID) {
            continue;
        }

        new numStart;

        while (numStart != -1) {
            numStart = strfind(actText, "@", true);
            if (numStart == -1) {
                break;
            }

            strdel(actText, numStart, numStart + 1);
            strins(actText, "\n", numStart, 144);
        }

        worldAction[world][i][vAction] = CreateDynamic3DTextLabel(actText, COLOR_PURPLE, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world);
        Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, worldAction[world][i][vAction], E_STREAMER_EXTRA_ID, i);

        pData[playerid][pRetVal][0] = i;
        tempWorld[world][vActionCount]++;
    }

    return true;
}

CB:ShowDialog(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        callBlock,
        type,
        str[1024];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dds[1024]", callBlock, type, str[1024])) {
        return SendMissCBMessage(playerid, blockid, actionid, "blockid type text");
    }

    if (callBlock < 0 || callBlock > VW[world][wMaxCB]) {
        return SendErrorCBMessage(playerid, blockid, actionid, "blockid", "1+");
    }

    if (type < 0 || type > 5) {
        return SendErrorCBMessage(playerid, blockid, actionid, "type", "0-5");
    }

    new numStart;

    while (numStart != -1) {
        numStart = strfind(str, "+", true);

        if (numStart == -1) {
            break;
        }

        strdel(str, numStart, numStart + 1);
        strins(str, "\t", numStart, 1024);
    }

    numStart = false;

    while (numStart != -1) {
        numStart = strfind(str, "@", true);

        if (numStart == -1) {
            break;
        }

        strdel(str, numStart, numStart + 1);
        strins(str, "\n", numStart, 1024);
    }

    if (!cmBlock[world][blockid][cbMode]) {


        pData[playerid][pRetVal][10] = callBlock;
        Dialog_Show(playerid, CBMainDialog, type, "\t{FFFFFF}[ Командный блок ]", str, "Y", "X");
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        pData[targetid][pRetVal][10] = callBlock;
        Dialog_Show(targetid, CBMainDialog, type, "\t{FFFFFF}[ Командный блок ]", str, "Y", "X");
    }

    return true;
}

CB:MoveCB(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        cbid,
        Float:x,
        Float:y,
        Float:z;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dfff", cbid, x, y, z)) {
        return SendMissCBMessage(playerid, blockid, actionid, "cbid x y z");
    }

    if (cbid < 0 || cbid > VW[world][wMAXCB]) {
        return SendErrorCBMessage(playerid, blockid, actionid, "cbid", "1+");
    }

    Streamer_SetFloatData(STREAMER_TYPE_AREA, cmBlock[world][cbid][cbID], E_STREAMER_X, x);
    Streamer_SetFloatData(STREAMER_TYPE_AREA, cmBlock[world][cbid][cbID], E_STREAMER_Y, y);
    Streamer_SetFloatData(STREAMER_TYPE_AREA, cmBlock[world][cbid][cbID], E_STREAMER_Z, z);

    return true;
}

CB:TimerOn(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        timerid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", timerid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "timerid");
    }

    timerid--;

    if (timerid < 0 || timerid > MAX_CB_TIMER) {
        return SendErrorCBMessage(playerid, blockid, actionid, "timerid", "1-10");
    }

    if (!CBTimer[world][timerid][cbtInterval]) {
        return false;
    }

    if (!CBTimer[world][timerid][cbtStatus]) {
        CBTimer[world][timerid][cbtID] = SetTimerEx("cbtTimerHandler", CBTimer[world][timerid][cbtInterval], true, "dddd", playerid, world, timerid, CBTimer[world][timerid[cbtBlock]]);
        CBTimer[world][timerid][cbtStatus] = true;
    }

    return true;
}

CB:TimerOff(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        timerid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", timerid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "timerid");
    }

    timerid--;

    if (timerid < 0 || timerid > MAX_CB_TIMER) {
        return SendErrorCBMessage(playerid, blockid, actionid, "timerid", "1-10");
    }

    if (CBTimer[world][timerid][cbtStatus]) {
        KillTimer(CBTimer[world][timerid][cbtID]);
        CBTimer[world][timerid][cbtStatus] = false;
    }

    return true;
}

CB:GiveTaser(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        toggle;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", toggle)) {
        return SendMissCBMessage(playerid, blockid, actionid, "toggle");
    }

    if (toggle != 0 || toggle != 1) {
        return SendErrorCBMessage(playerid, blockid, actionid, "toggle", "0/1");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        if (toggle) {
            if (pData[playerid][pTazer]) {
                return false;
            }

            pData[playerid][pTazer] = true;

            pData[playerid][pGuns][2] = dgun[playerid][weapon_slot][2];
            pData[playerid][pAmmo][2] = dgun[playerid][ammo_slot][2];

            GiveGun(playerid, 23, 1);
        } else {
            if (!pData[playerid][pTazer]) {
                return false;
            }

            pData[playerid][pTazer] = false;

            if (pData[playerid][pGuns][2]) {
                GiveGun(playerid, pData[playerid][pGuns][2], pData[playerid][pAmmo][2]);
            } else {
                GiveGun(playerid, 24, 0);
            }
        }
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            return false;
        }

        if (toggle) {
            if (pData[targetid][pTazer]) {
                return false;
            }

            pData[targetid][pTazer] = true;

            pData[targetid][pGuns][2] = dgun[targetid][weapon_slot][2];
            pData[targetid][pAmmo][2] = dgun[targetid][ammo_slot][2];

            GiveGun(targetid, 23, 1);
        } else {
            if (!pData[targetid][pTazer]) {
                return false;
            }

            pData[targetid][pTazer] = false;

            if (pData[targetid][pGuns][2]) {
                GiveGun(targetid, pData[targetid][pGuns][2], pData[targetid][pAmmo][2]);
            } else {
                GiveGun(targetid, 24, 0);
            }
        }
    }

    return true;
}

CB:SetPlate(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        str[32];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "s[32]", str)) {
        return SendMissCBMessage(playerid, blockid, actionid, "str");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        if (GetPlayerVehicleSeat(playerid) != 0) {
            return false;
        }

        SetVehicleNumberPlate(GetPlayerVehicleID(playerid), str);
        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            return false;
        }

        if (GetPlayerVehicleSeat(targetid) != 0) {
            return false;
        }

        SetVehicleNumberPlate(GetPlayerVehicleID(targetid), str);
        SetVehicleToRespawn(GetPlayerVehicleID(targetid));
    }

    return true;
}

CB:SetOwner(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        ownerid,
        vehicleid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dd", vehicleid, ownerid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "vehicleid ownerid");
    }

    if (ownerid < 0 || ownerid > MAX_PLAYERS) {
        return SendErrorCBMessage(playerid, blockid, actionid, "0+");
    }

    if (vehicleid < 1 || vehicleid > MAX_VEHICLES) {
        return SendErrorCBMessage(playerid, blockid, actionid, "1+");
    }

    if (!cbCompare(ownerid, blockid, world)) {
        return false;
    }

    if (GetVehicleVirtualWorld(vehicleid) != world) {
        return false;
    }

    vData[vehicleid][vOwner] = pdata[ownerid][pID];
    return true;
}

CB:SetVehicleAttach(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        slotid,
        modelid,
        Float:x,
        Float:y,
        Float:z,
        Float:rx,
        Float:ry,
        Float:rz;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "ddffffff", slotid, modelid, x, y, z, rx, ry, rz)) {
        return SendMissCBMessage(playerid, blockid, actionid, "slotid modelid x y z rx ry rz");
    }

    slotid--;

    if (slotid < 0 || slotid > 9) {
        return SendErrorCBMessage(playerid, blockid, actionid, "slotid", "1-10");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        if (GetPlayerVehicleSeat(playerid) != 0) {
            return false;
        }

        new vehicleid = GetPlayerVehicleID(playerid);

        if (vData[vehicleid][vattach][slotid]) {
            Streamer_SetIntData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_MODEL_ID, modelid),
                Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_OFFSET_X, x);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_OFFSET_Y, y);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_OFFSET_Z, z);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_R_X, rx);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_R_Y, ry);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_R_Z, rz);
        } else {
            vData[vehicleid][vattach][slotid] = CreateDynamicObject(modelid, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, world);
            AttachDynamicObjectToVehicle(vData[vehicleid][vattach][slotid], vehicleid, x, y, z, rx, ry, rz);
        }
        return true;
    }

    foreach(new targetid : Player) {

        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        if (GetPlayerVehicleSeat(targetid) != 0) {
            continue;
        }

        new vehicleid = GetPlayerVehicleID(i);

        if (vData[vehicleid][vattach][slotid]) {
            Streamer_SetIntData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_MODEL_ID, modelid),
                Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_OFFSET_X, x);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_OFFSET_Y, y);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_OFFSET_Z, z);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_R_X, rx);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_R_Y, ry);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, vData[vehicleid][vattach][slotid], E_STREAMER_ATTACH_R_Z, rz);
        } else {
            vData[vehicleid][vattach][slotid] = CreateDynamicObject(modelid, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, world);
            AttachDynamicObjectToVehicle(vData[vehicleid][vattach][slotid], vehicleid, x, y, z, rx, ry, rz);
        }
    }

    return true;
}

CB:UnVehicleAttach(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        slotid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", slotid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "slotid");
    }

    slotid--;

    if (slotid < 0 || slotid > 9) {
        retun SendErrorCBMessage(playerid, blockid, actionid, "slotid", "1-10");
    }

    if (!cmBlock[world][blockid][cbMode]) {

        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        if (GetPlayerVehicleSeat(playerid) != 0) {
            return false;
        }

        new vehicleid = GetPlayerVehicleID(playerid);

        if (vData[vehicleid][vattach][slotid]) {
            if (IsValidDynamicObject(vData[vehicleid][vattach][slotid]))
                DestroyDynamicObject(vData[vehicleid][vattach][slotid]);

            vData[vehicleid][vattach][slotid] = false;
        }

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        if (GetPlayerVehicleSeat(targetid) != 0) {
            continue;
        }

        new vehicleid = GetPlayerVehicleID(targetid);

        if (vData[vehicleid][vattach][slotid]) {
            if (IsValidDynamicObject(vData[vehicleid][vattach][slotid]))
                DestroyDynamicObject(vData[vehicleid][vattach][slotid]);

            vData[vehicleid][vattach][slotid] = false;
        }
    }

    return true;
}

CB:SetVehiclePos(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        vehicleid,
        Float:x, Float:y, Float:z, Float:rx;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dfffF(0.0)", vehicleid, x, y, z, rx)) {
        return SendMissCBMessage(playerid, blockid, actionid, "vehicleid x y z rx");
    }

    if (vehicleid < 1 || vehicle > MAX_VEHICLES) {
        return SendErrorCBMessage(playerid, blockid, actionid, "1+");
    }


    if (GetVehicleVirtualWorld(vehicleid) != world) {
        return false;
    }

    SetVehiclePos(vehicleid, x, y, z);
    SetVehicleZAngle(vehicleid, rx);
    return true;
}

CB:SetPlayerAngle(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        Float:angle;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "f", angle)) {
        return SendMissCBMessage(playerid, blockid, actionid, "agnle");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerFacingAngle(playerid, angle);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerFacingAngle(targetid, angle);
    }

    return true;
}

CB:SetNameTag(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        status;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", status)) {
        return SendMissCBMessage(playerid, blockid, actionid, "status");
    }

    if (status != 1 && status != 0) {
        return SendErrorCBMessage(playerid, blockid, actionid, "status", "0/1");
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        ShowPlayerNameTagForPlayer(playerid, targetid, status);
    }

    status = !status;
    pData[playerid][pHideName] = status;

    return true;
}

CB:ActorCreate(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        skin,
        Float:x, Float:y, Float:z, Float:rz;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dffff", skin, x, y, z, rz)) {
        return SendMissCBMessage(playerid, blockid, actionid, "skin x y z angle");
    }

    if (skin < 0 || skin > 311) {
        return SendErrorCBMessage(playerid, blockid, actionid, "skin", "0-311");
    }

    pData[playerid][pRetVal][0] = addTempActor(world, skin, x, y, z, rx, world, -1);
    return true;
}

CB:ActorDelete(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        actorid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments "d", actorid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actorid");
    }

    if (actorid < 0 || actorid > MAX_ACTOR_SLOT) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actorid", "0+");
    }

    if (!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
        return false;
    }

    if (actorSystem[tempWorld[world][aSlot][actorid]][aNameID] != Text3D:INVALID_3DTEXT_ID) {
        DestroyDynamic3DTextLabel(actorSystem[tempWorld[world][aSlot][actorid]][aNameID]);
    }

    DestroyDynamicActor(tempWorld[world][aSlot][actorid]);

    actorSystem[tempWorld[world][aSlot][actorid]][localID] = false;
    actorSystem[tempWorld[world][aSlot][actorid]][aStatus] = false;
    actorSystem[tempWorld[world][aSlot][actorid]][UsedAnim] = false;
    actorSystem[tempWorld[world][aSlot][actorid]][AltAnim] = false;
    actorSystem[tempWorld[world][aSlot][actorid]][aNameID] = Text3D:INVALID_3DTEXT_ID;

    tempWorld[world][aSlot][actorid] = false;

    return true;
}

CB:ActorSetSkin(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        actorid,
        skin;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dd", actorid, skin)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actorid skin");
    }

    if (actorid < 0 || actorid > MAX_ACTOR_SLOT) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actorid", "0+");
    }

    if (!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
        return false;
    }

    Streamer_SetIntData(STREAMER_TYPE_ACTOR, tempWorld[world][aSlot][actorid], E_STREAMER_MODEL_ID, skin);
    return true;
}

CB:ActorSetPos(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        actorid,
        Float:x, Float:y, Float:z;

    ReadAmxMemoryArray(argumentIdx, arguments;)

    iF(sscanf(arguments, "dfff", actorid, x, y, z)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actorid x y z");
    }

    if (actorid < 0 || actorid > MAX_ACTOR_SLOT) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actorid", "0+");
    }

    if (!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
        return false;
    }

    if (actorSystem[tempWorld[world][aSlot][actorid]][aNameID] != Text3D:INVALID_3DTEXT_ID) {
        Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, actorSystem[tempWorld[world][aSlot][actorid]][aNameID], E_STREAMER_X, x);
        Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, actorSystem[tempWorld[world][aSlot][actorid]][aNameID], E_STREAMER_Y, y);
        Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, actorSystem[tempWorld[world][aSlot][actorid]][aNameID], E_STREAMER_Z, z + 1.1);
    }

    SetDynamicActorPos(tempWorld[world][aSlot][actorid], x, y, z);
    return true;
}

CB:ActorSetAngle(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        actorid,
        Float:rx;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "df", actorid, rx)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actorid angle");
    }

    if (actorid < 0 || actorid > MAX_ACTOR_SLOT) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actorid", "0+");
    }

    if (!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
        return false;
    }

    SetDynamicActorFacingAngle(tempWorld[world][aSlot][actorid], rx);
    return true;
}

CB:ActorSetAnim(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        actorid,
        animid;

    ReadAmxMemoryArray(argumentIdx, arguments;)

    if (sscanf(arguments, "dd", actorid, animid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actorid animid");
    }

    if (actorid < 0 || actorid > MAX_ACTOR_SLOT) {
        return SendErrorCBMessage(playerid, blockid, actionid, "actorid", "0+");
    }

    if (animid < 0 || animid > sizeof(actorAnim)) {
        return SendErrorCBMessage(playerid, blockid, actionid, "animid", "0+");
    }

    if (!IsValidDynamicActor(tempWorld[world][aSlot][actorid])) {
        return false;
    }

    ApplyDynamicActorAnimation(tempWorld[world][aSlot][actorid], actorAnim[animid][aLib], actorAnim[animid][aAnim], actorAnim[animid][aDelta], actorAnim[animid][aLoop], 0, 0, actorAnim[animid][aFreeze], 0);
    actorSystem[tempWorld[world][aSlot][actorid]][UsedAnim] = animid;

    SetDynamicActorHealth(tempWorld[world][aSlot][actorid], 100.0);
    return true;
}

CB:PlayerRess(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {
        World_PlayerReviwe(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        World_PlayerReviwe(targetid);
    }

    return true;
}

CB:PlayerSetDeath(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        time;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", time)) {
        return SendMissCBMessage(playerid, blockid, actionid, "time");
    }

    if (time < 0 || time > 999) {
        return SendErrorCBMessage(playerid, blockid, actionid, "time", "0-999");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        pData[playerid][pDead] = true;
        pData[playerid][pDeadStage] = time;
        GetPlayerPos(playerid, pData[playerid][pDeadX], pData[playerid][pDeadY], pData[playerid][pDeadZ]);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        pData[targetid][pDead] = true;
        pData[targetid][pDeadStage] = time;
        GetPlayerPos(playerid, pData[targetid][pDeadX], pData[targetid][pDeadY], pData[targetid][pDeadZ]);
    }

    return true;
}

CB:setWorldTime(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        time;

    if (sscanf(arguments, "d", time)) {
        return SendMissCBMessage(playerid, blockid, actionid, "time");
    }

    if (time < 0 || time > 24) {
        return SendErrorCBMessage(playerid, blockid, actionid, "time", "0-24");
    }

    VW[world][vTime] = time;

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (GetPlayerVirtualWorld(targetid) == world) {
            SetPlayeTime(targetid, time, 0);
        }
    }

    return true;
}

CB:setWorldWeather(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        weather;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", weather)) {
        return SendMissCBMessage(playerid, blockid, actionid, "weather");
    }

    if (weather < 0 || weather > 255) {
        return SendErrorCBMessage(playerid, blockid, actionid, "weather", "0-255");
    }

    VW[world][vWeather] = weather;

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (GetPlayerVirtualWorld(targetid) == world) {
            SetPlayerWeather(targetid, weather);
        }
    }

    return true;
}

CB:VehicleStatus(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    slot,
    status;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dd", slot, status)) {
        return SendMissCBMessage(playerid, blockid, actionid, "slot status");
    }

    if (status != 0 && status != 1) {
        return SendErrorCBMessage(playerid, blockid, actionid, "status", "0-1");
    }

    if (slot < 0 || slot > 6) {
        return SendErrorCBMessage(playerid, blockid, actionid, "slot", "0-3");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        SetVehicleParams(GetPlayerVehicleID(playerid), slot, status);
        return true;
    }

    foreach(new targetid : Player) {
        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetVehicleParams(GetPlayerVehicleID(targetid), slot, status);
    }

    return true;
}

CB:VehWindowStatus(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        slot,
        status;

    ReadAmxMemoryArray(argumentIdx, arguments;)

    if (sscanf(arguments, "dd", slot, status)) {
        return SendMissCBMessage(playerid, blockid, actionid, "slot status");
    }

    if (status != 0 && status != 1) {
        return SendErrorCBMessage(playerid, blockid, actionid, "status", "0-1");
    }

    if (slot < 0 || slot > 3) {
        return SendErrorCBMessage(playerid, blockid, actionid, "slot", "0-3");
    }

    if (!cmBlock[world][blockid][cbMode]) {


        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        SetVehicleWindow(GetPlayerVehicleID(playerid), slot, status);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        SetVehicleWindow(GetPlayerVehicleID(targetid), slot, status);
    }
}

CB:SetVehicleTires(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        wheels[4];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dddd", wheels[0], wheels[1], wheels[2], wheels[3])) {
        return SendMissCBMessage(playerid, blockid, actionid, "wheel0 wheel1 wheel2 wheel3");
    }

    for (new wheel; wheel < sizeof(wheels); wheel++) {
        if (wheels[wheel] < 0 || wheels[wheel] > 2) {
            return SendErrorCBMessage(playerid, blockid, actionid, "wheels", "0-2");
        }
    }

    if (!cmBlock[world][blockid][cbMode]) {


        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        if (GetPlayerVehicleSeat(playerid) != 0) {
            return false;
        }

        new tempTires[4], panels, doors, lights, tires;

        GetVehicleDamageStatus(GetPlayerVehicleID(playerid), panels, doors, lights, tires);
        decode_tires(tires, tempTires[0], tempTires[1], tempTires[2], tempTires[3]);

        for (new wheel; wheel < sizeof(wheels); wheel++) {
            if (wheels[wheel] == 2) {
                continue;
            }

            tempTires[wheel] = wheels[wheel];
        }

        UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid), panels, doors, lights, encode_tires(tempTires[0], tempTires[1], tempTires[2], tempTires[3]));
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        if (GetPlayerVehicleSeat(targetid) != 0) {
            continue;
        }

        new tempTires[4], panels, doors, lights, tires;

        GetVehicleDamageStatus(GetPlayerVehicleID(targetid), panels, doors, lights, tires);
        decode_tires(tires, tempTires[0], tempTires[1], tempTires[2], tempTires[3]);

        for (new wheel; wheel < sizeof(wheels); wheel++) {
            if (wheels[wheel] == 2) {
                continue;
            }

            tempTires[wheel] = wheels[wheel];
        }

        UpdateVehicleDamageStatus(GetPlayerVehicleID(targetid), panels, doors, lights, encode_tires(tempTires[0], tempTires[1], tempTires[2], tempTires[3]));
    }

    return true;
}

CB:PutPlayerInVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        vehicleid,
        slot;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dd", vehicleid, slot)) {
        return SendMissCBMessage(playerid, blockid, actionid, "vehid slot");
    }

    if (vehicleid < 1 || vehicleid > MAX_VEHICLES) {
        return SendErrorCBMessage(playerid, blockid, actionid, "vehid", "1+")
    }

    if (!cbCompareMode(playerid, blockid, world)) {
        return false;
    }

    if (GetVehicleVirtualWorld(vehicleid) != world) {
        return false;
    }

    PutPlayerVeh(playerid, vehicleid, slot);
    return true;
}

CB:KickPlayerFromVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {


        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        RemovePlayerFromVehicle(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        RemovePlayerFromVehicle(targetid);
    }

    return true;
}

CB:SetPvar(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        var [32],
        data[144];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "p<,>s[32]s[144]",
            var, data)) {
        return SendMissCBMessage(playerid, blockid, actionid, "var, data");
    }

    if (setVarData(world,
            var, data) == INVALID_VECTOR_INDEX) {
        return false;
    }

    return true;
}

CB:SetPlayerWorldMute(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        time,
        userid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "p<,>dD(-1)", time, userid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "time, userid");
    }

    if (time < 0 || time > 10000) {
        return SendErrorCBMessage(playerid, blockid, actionid, "time", "0-10000");
    }

    userid = resolveTargetOrSelf(userid, playerid);

    if (!cbCompareMode(userid, blockid, world)) {
        return false;
    }

    pData[userid][pWorldMute] = gettime() + time * 60;
    return true;
}

CB:SetPlayerCameraPos(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT];

    new
    Float:x, Float:y, Float:z,
    Float:atX, Float:atY, Float:atZ;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "ffffff", x, y, z, atX, atY, atZ)) {
        return SendMissCBMessage(playerid, blockid, actionid, "x y z atX atY atZ")
    }

    if (!cmBlock[world][blockid][cbMode]) {


        TogglePlayerSpectating(playerid, true);
        SetPlayerCameraPos(playerid, x, y, z);
        SetPlayerCameraLookAt(playerid, atX, atY, atZ);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        TogglePlayerSpectating(targetid, true);
        SetPlayerCameraPos(targetid, x, y, z);
        SetPlayerCameraLookAt(targetid, atX, atY, atZ);
    }

    return true;
}

CB:SetPlayerCameraLookAt(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        Float:x, Float:y, Float:z;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "fff", x, y, z)) {
        return SendMissCBMessage(playerid, blockid, actionid, "x y z");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerCameraLookAt(playerid, x, y, z);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerCameraLookAt(targetid, x, y, z);
    }

    return true;
}

CB:ReturnPlayerCamera(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (!cmBlock[world][blockid][cbMode]) {
        TogglePlayerSpectating(playerid, false);
        SetCameraBehindPlayer(playerid)
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        TogglePlayerSpectating(targetid, false);
        SetCameraBehindPlayer(targetid);
    }

    return true;
}

CB:CallTriggerBlock(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        callBlock[24],
        data;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "p<,>s[24]d", callBlock, data)) {
        return SendMissCBMessage(playerid, blockid, actionid, "callBlock, data");
    }

    if (OnCallSwitchBlock(playerid, callBlock, world, data) == 0) {
        return false;
    }

    return true;
}

CB:SetObjectArray(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid,
        value;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "dd", objectid, value)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid value");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid)
    if (objectid <= 0) {
        return SendErrorCBMessage(playerid, blockid, actionid, "objectid", "> 0");
    }

    Streamet_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_CUSTOM(1237), value);

    return true;
}

CB:AttachCameraToObject(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
    arguments[TEXT_FUNCTION_ARGUMENT],
        objectid;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", objectid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "objectid");
    }

    objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
    if (objectid <= 0) {
        return SendErrorCBMessage(playerid, blockid, actionid, "objectid", "valid_object");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        AttachCameraToObject(playerid, objectid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        AttachCameraToObject(targetid, objectid);
    }

    return true;
}

CB:UnObjectCamera(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {
        SetCameraBehindPlayer(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        SetCameraBehindPlayer(targetid);
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

CB:addArmor(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: arm,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "f", arm))
        return SendMissCBMessage(playerid, blockid, actionid, "armour");

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerHealth(playerid, pData[playerid][pArmour] + arm);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerHealth(targetid, pData[targetid][pArmour] + arm);
    }
    return true;
}

CB:setPos(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: x,
    Float: y,
    Float: z,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "fff", x, y, z))
        return SendMissCBMessage(playerid, blockid, actionid, "x y z");

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerPos(playerid, x, y, z);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerPos(targetid, x, y, z);
    }
    return true;
}

CB:setSkin(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new skin,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", skin))
        return SendMissCBMessage(playerid, blockid, actionid, "skin");

    if (0 > skin > 311)
        return SendErrorCBMessage(playerid, blockid, actionid, "skin", "0-311");

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerSkin(playerid, skin);
        pData[playerid][pSkin] = skin;
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerSkin(targetid, skin);
        pData[targetid][pSkin] = skin;
    }
    return true;
}

CB:setTime(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new time,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", time))
        return SendMissCBMessage(playerid, blockid, actionid, "time");

    if (0 > time > 24)
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

CB:setWeather(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new weather,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", weather))
        return SendMissCBMessage(playerid, blockid, actionid, "weather");

    if (0 > weather > 255)
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

CB:resetWeapom(const playerid, const blockid, const actionid, const world, const argumentIdx) {

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

    if (VW[world][vDev])
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

    if (!cmBlock[world][blockid][cbMode]) {
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

    if (!cmBlock[world][blockid][cbMode]) {
        pData[playerid][pTeam] = teamid;

        if (teamid != -1) {
            if (worldTeam[world][teamid][tSkin]) {
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

        if (teamid != -1) {
            if (worldTeam[world][teamid][tSkin]) {
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

    if (!cmBlock[world][blockid][cbMode]) {
        if (freeze)
            ApplyAnimationEx(playerid, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);
        else
            ApplyAnimation(playerid, lib, anim, 4.1, loop, 1, 1, freeze, 0, 1);

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (freeze)
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

    if (!cmBlock[world][blockid][cbMode]) {

        if (IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
        GetPlayerFacingAngle(playerid, playerPos[3]);
        interior = GetPlayerInterior(playerid);

        vehicleid = CreateVehicleEx(model[0], playerPos, color1, color2, world, interior, siren);

        if (vehicleid == -1) {
            return SendMissCBMessage(playerid, blockid, actionid, "Достигнут лимит транспорта!");
        }

        pData[playerid][pRetVal][0] = vehicleid;

        vData[tempWorld[world][vehSlot][vehicleid]][vOwner] = pData[playerid][pID];
        vData[tempWorld[world][vehSlot][vehicleid]][vTeam] = -1;

        PutPlayerVeh(playerid, tempWorld[world][vehSlot][vehicleid], 0);

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (IsPlayerInAnyVehicle(targetid)) {
            return false;
        }

        GetPlayerPos(targetid, playerPos[0], playerPos[1], playerPos[2]);
        GetPlayerFacingAngle(targetid, playerPos[3]);
        interior = GetPlayerInterior(targetid);

        vehicleid = CreateVehicleEx(model[0], playerPos, color1, color2, world, interior, siren);

        if (vehicleid == -1) {
            return SendMissCBMessage(targetid, blockid, actionid, "Достигнут лимит транспорта!");
        }

        pData[targetid][pRetVal][0] = vehicleid;

        vData[tempWorld[world][vehSlot][vehicleid]][vOwner] = pData[targetid][pID];
        vData[tempWorld[world][vehSlot][vehicleid]][vTeam] = -1;

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

    if (!cmBlock[world][blockid][cbMode]) {

        if (!IsPlayerInAnyVehicle(playerid))
            continue;

        SetVehicleHealth(GetPlayerVehicleID(playerid), health);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
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

    if (!cmBlock[world][blockid][cbMode]) {

        if (!IsPlayerInAnyVehicle(playerid))
            continue;
        GetVehicleHealth(GetPlayerVehicleID(playerid), oldhealth);
        SetVehicleHealth(GetPlayerVehicleID(playerid), oldhealth + health);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
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
        if (GetVehicleVirtualWorld(vehicleid) != world) {
            return false;
        }
        vData[vehicleid][vArray][slot] = value;
        return true;
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }
        vehicleid = GetPlayerVehicleID(playerid);
        vData[vehicleid][vArray][slot] = value;
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
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

    if (GetVehicleVirtualWorld(vehicleid) != world) {
        return false
    }

    if (vehicleid != 0) {
        if (GetVehicleVirtualWorld(vehicleid) != world) {
            return false;
        }
        vData[vehicleid][vArray][slot] += value;
        return true;
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }
        vehicleid = GetPlayerVehicleID(playerid);
        vData[vehicleid][vArray][slot] += value;
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        vehicleid = GetPlayerVehicleID(targetid);
        vData[vehicleid][vArray][slot] += value;
    }

    return true;
}


CB:spawnVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }
        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        SetVehicleToRespawn(GetPlayerVehicleID(targetid));
    }

    return true;
}

CB:sprayVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new color1,
    color2,
    vehicleid,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "ddD(0)", color1, color2, vehicleid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "color1 color2 [vehicleid]");
    }

    if (vehicleid != 0) {
        if (0 > vehicleid > MAX_VEHICLES) {
            return false;
        }

        if (GetVehicleVirtualWorld(vehicleid) != world) {
            return false;
        }

        ChangeVehicleColor(vehicleid, color1, color2);
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        ChangeVehicleColor(GetPlayerVehicleID(playerid), color1, color2);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        ChangeVehicleColor(GetPlayerVehicleID(targetid), color1, color2);
    }

    return true;
}

CB:addVehComp(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new vehComp,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", vehComp)) {
        return SendMissCBMessage(playerid, blockid, actionid, "vehicleComponent");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        AddVehicleComponent(GetPlayerVehicleID(playerid), vehComp);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        AddVehicleComponent(GetPlayerVehicleID(targetid), vehComp);
    }

    return true;
}

CB:delVehComp(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new vehComp,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", vehComp)) {
        return SendMissCBMessage(playerid, blockid, actionid, "vehicleComponent");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        RemoveVehicleComponent(GetPlayerVehicleID(playerid), vehComp);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        RemoveVehicleComponent(GetPlayerVehicleID(targetid), vehComp);
    }

    return true;
}

CB:delVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new vehicleid,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", vehicleid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "vehicleID");
    }

    if (vehicleid > 0) {
        if (1 > vehicleid > MAX_VEHICLES) {
            return false;
        }

        if (GetVehicleVirtualWorld(vehicleid) != world) {
            return false;
        }

        DestroyVehicleEx(vehicleid, world);
        return true;
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        DestroyVehicleEx(GetPlayerVehicleID(playerid), vehComp);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        DestroyVehicleEx(GetPlayerVehicleID(targetid), vehComp);
    }

    return true;
}

CB:fixVeh(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new vehicleid,
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

        if (GetVehicleVirtualWorld(vehicleid) != world) {
            return false;
        }

        GetVehicleHealth(vehicleid, health);

        RepairVehicle(vehicleid);
        SetVehicleHealth(vehicleid, health);
        return true;
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (!IsPlayerInAnyVehicle(playerid)) {
            return false;
        }

        GetVehicleHealth(GetPlayerVehicleID(playerid), health);

        RepairVehicle(GetPlayerVehicleID(playerid));
        SetVehicleHealth(GetPlayerVehicleID(playerid), health);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (!IsPlayerInAnyVehicle(targetid)) {
            continue;
        }

        GetVehicleHealth(GetPlayerVehicleID(targetid), health);

        RepairVehicle(GetPlayerVehicleID(targetid));
        SetVehicleHealth(GetPlayerVehicleID(targetid), health);
    }

    return true;
}

CB:setScore(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new score,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", score)) {
        return SendMissCBMessage(playerid, blockid, actionid, "score");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerScore(playerid, score);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerScore(targetid, score);
    }

    return true;
}

CB:addScore(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new score,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", score)) {
        return SendMissCBMessage(playerid, blockid, actionid, "score");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerScore(playerid, GetPlayerScore(playerid) + score);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerScore(targetid, GetPlayerScore(targetid) + score);
    }

    return true;
}

CB:setWanted(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new level,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", level)) {
        return SendMissCBMessage(playerid, blockid, actionid, "level");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerWantedLevel(playerid, level);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerWantedLevel(targetid, level);
    }

    return true;
}

CB:addWanted(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new level,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", level)) {
        return SendMissCBMessage(playerid, blockid, actionid, "level");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + level);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerWantedLevel(targetid, GetPlayerWantedLevel(targetid) + level);
    }

    return true;
}

CB:SetPlayerCP(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: x,
    Float: y,
    Float: z,
    Float: size,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "ffff", x, y, z, size)) {
        return SendMissCBMessage(playerid, blockid, actionid, "x y z size");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerCheckpoint(playerid, x, y, z, size);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerCheckpoint(targetid, x, y, z, size);
    }

    return true;
}

CB:DisablePlayerCP(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    if (!cmBlock[world][blockid][cbMode]) {
        DisablePlayerCheckpoint(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        DisablePlayerCheckpoint(targetid);
    }

    return true;
}

CB:SetPlayerRaceCP(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: x,
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

    if (0 > type > 8) {
        return SendErrorCBMessage(playerid, blockid, actionid, "type", "0-8");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerRaceCheckpoint(playerid, type, x, y, z, nx, ny, nz, size);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerRaceCheckpoint(targetid, type, x, y, z, nx, ny, nz, size);
    }

    return true;
}

CB:DisablePlayerRaceCP(const playerid, const blockid, const actionid, const world, const argumentIdx) {

    if (!cmBlock[world][blockid][cbMode]) {
        DisablePlayerRaceCheckpoint(playerid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        DisablePlayerRaceCheckpoint(targetid);
    }

    return true;
}

CB:SetPlayerMapIcon(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new iconid,
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

    if (0 > iconid > 99) {
        return SendErrorCBMessage(playerid, blockid, actionid, "iconid", "0-99");
    }

    if (0 > markertype > 63) {
        return SendErrorCBMessage(playerid, blockid, actionid, "markertype", "0-63");
    }

    if (0 > style > 4) {
        return SendErrorCBMessage(playerid, blockid, actionid, "style", "0-4");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerMapIcon(playerid, iconid, x, y, z, markertype, color, style);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerMapIcon(targetid, iconid, x, y, z, markertype, color, style);
    }

    return true;
}

CB:RemovePlayerMapIcon(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new iconid,

    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", iconid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "iconid");
    }

    if (0 > iconid > 99) {
        return SendErrorCBMessage(playerid, blockid, actionid, "iconid", "0-99");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        RemovePlayerMapIcon(playerid, iconid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        RemovePlayerMapIcon(targetid, iconid);
    }

    return true;
}

CB:SetPlayerAttach(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new iconid,

    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", slotid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "slotid");
    }

    slotid--;
    if (0 > slotid > 9) {
        return SendErrorCBMessage(playerid, blockid, actionid, "slotid", "1-10");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        if (sscanf(arguments, "p< >ddddfffffffff",
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
            )) return false;

        SetPlayerAttach(playerid);
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (sscanf(arguments, "p< >ddddfffffffff",
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
            )) break;

        SetPlayerAttach(targetid);
    }

    return true;
}

CB:DelPlayerAttach(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new slotid,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", slotid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "slotid");
    }

    slotid--;
    if (0 > slot > 9) {
        return SendErrorCBMessage(playerid, blockid, actionId, "slotid", "1-10")
    }

    if (!cmBlock[world][blockid][cbMode]) {

        if (slotid == 0) {
            for (new t; t < 10; t++) {
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

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        if (slotid == 0) {
            for (new t; t < 10; t++) {
                pAttach[targetid][t][0] = false;
                pAttach[targetid][t][1] = false;
                RemovePlayerAttachedObject(targetid, t);
            }
        } else {
            pAttach[targetid][slotid][0] = false;
            pAttach[targetid][slotid][1] = false;
            RemovePlayerAttachedObject(targetid, slotid);
        }
    }

    return true;
}

CB:ActivateGate(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new gateSlot,
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

    if (type == 0) {
        worldGate[world][gateSlot][gStatus] = !worldGate[world][gateSlot][gStatus];

        if (worldGate[world][gateSlot][gStatus])
            MoveDynamicObject(worldGate[world][gateSlot][gID], worldGate[world][gateSlot][gPosEndX], worldGate[world][gateSlot][gPosEndY], worldGate[world][gateSlot][gPosEndZ], worldGate[world][gateSlot][gSpeed], worldGate[world][gateSlot][gPosEndRX], worldGate[world][gateSlot][gPosEndRY], worldGate[world][gateSlot][gPosEndRZ]);
        else
            MoveDynamicObject(worldGate[world][gateSlot][gID], worldGate[world][gateSlot][gPosStartX], worldGate[world][gateSlot][gPosStartY], worldGate[world][gateSlot][gPosStartZ], worldGate[world][gateSlot][gSpeed], worldGate[world][gateSlot][gPosStartRX], worldGate[world][gateSlot][gPosStartRY], worldGate[world][gateSlot][gPosStartRZ]);
    } else if (type == 1) {
        worldGate[world][gateSlot][gStatus] = true;
        MoveDynamicObject(worldGate[world][gateSlot][gID], worldGate[world][gateSlot][gPosEndX], worldGate[world][gateSlot][gPosEndY], worldGate[world][gateSlot][gPosEndZ], worldGate[world][gateSlot][gSpeed], worldGate[world][gateSlot][gPosEndRX], worldGate[world][gateSlot][gPosEndRY], worldGate[world][gateSlot][gPosEndRZ]);
    } else if (type == 2) {
        worldGate[world][gateSlot][gStatus] = false;
        MoveDynamicObject(worldGate[world][gateSlot][gID], worldGate[world][gateSlot][gPosStartX], worldGate[world][gateSlot][gPosStartY], worldGate[world][gateSlot][gPosStartZ], worldGate[world][gateSlot][gSpeed], worldGate[world][gateSlot][gPosStartRX], worldGate[world][gateSlot][gPosStartRY], worldGate[world][gateSlot][gPosStartRZ]);
    }

    return true;
}

CB:specialAction(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new actionid,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "d", actionid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "actionid");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerSpecialAction(playerid, actionid);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerSpecialAction(targetid, actionid);
    }

    return true;
}

CB:SetEnum(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new slot,
    param,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "df", slot, param)) {
        return SendMissCBMessage(playerid, blockid, actionid, "slot param");
    }

    if (0 > slot > 26) {
        return SendErrorCBMessage(playerid, blockid, actionId, "slot", "0-26");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        pData[playerid][cbData][slot] = floatround(param);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        pData[targetid][cbData][slot] = floatround(param);
    }

    return true;
}

CB:AddEnum(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new slot,
    param,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "df", slot, param)) {
        return SendMissCBMessage(playerid, blockid, actionid, "slot param");
    }

    if (0 > slot > 26) {
        return SendErrorCBMessage(playerid, blockid, actionId, "slot", "0-26");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        pData[playerid][cbData][slot] += floatround(param);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        pData[targetid][cbData][slot] += floatround(param);
    }

    return true;
}

CB:SetClist(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new color,
    arguments[TEXT_FUNCTION_ARGUMENT];

    ReadAmxMemoryArray(argumentIdx, arguments);

    if (sscanf(arguments, "x", color)) {
        return SendMissCBMessage(playerid, blockid, actionid, "color");
    }

    if (!cmBlock[world][blockid][cbMode]) {
        SetPlayerColor(playerid, color);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        SetPlayerColor(targetid, color);
    }

    return true;
}

CB:GameText(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new str[64],
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

    if (!cmBlock[world][blockid][cbMode]) {
        GameTextForPlayer(targetid, str, time, style);
        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        GameTextForPlayer(targetid, str, time, style);
    }

    return true;
}

CB:CreateExplosion(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new type,
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

    if (!x && !y && !z) {
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
    new slot,
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
    new slot,
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

    if (!cmBlock[world][blockid][cbMode]) {
        PlayCrimeReportForPlayer(playerid, suspectid, crimeid);

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        PlayCrimeReportForPlayer(targetid, suspectid, crimeid);
    }


    return true;
}


CB:InterpolateCamera(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new Float: startX,
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

    if (!cmBlock[world][blockid][cbMode]) {
        TogglePlayerSpectating(playerid, true);
        if (meth == 0)
            InterpolateCameraPos(playerid, startX, startY, startZ, stopX, stopY, stopZ, time, CAMERA_MOVE);
        else
            InterpolateCameraLookAt(playerid, startX, startY, startZ, stopX, stopY, stopZ, time, CAMERA_MOVE);

        return true;
    }

    foreach(new targetid : Player) {
        if (!cbCompareMode(targetid, blockid, world)) {
            continue;
        }

        TogglePlayerSpectating(targetid, true);
        if (meth == 0)
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

CB:ActionMe(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new arguments[TEXT_FUNCTION_ARGUMENT];
    
 ReadAmxMemoryArray(argumentIdx, arguments);

  if(isnull(arguments)) {
    return SendMissCBMessage(playerid, blockid, actionid, "string");
  }

  if(!cmBlock[world][blockid][cbMode]) {
		cmd_me(playerid, arguments);
		return true;
	}

  foreach(new targetid : Player) {
    if(!cbCompareMode(targetid, blockid, world)) {
      continue;
    }

    cmd_me(targetid, arguments);
  }


  return true;
}

CB:ActionAme(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new arguments[TEXT_FUNCTION_ARGUMENT];
    
  ReadAmxMemoryArray(argumentIdx, arguments);

  if (isnull(arguments)) {
    return SendMissCBMessage(playerid, blockid, actionid, "string");
  }

  if(!cmBlock[world][blockid][cbMode]) {
		cmd_ame(playerid, arguments);
		return true;
	}

  foreach(new targetid : Player) {
    if(!cbCompareMode(targetid, blockid, world)) {
      continue;
    }

    cmd_ame(targetid, arguments);
  }


  return true;
}

CB:ActionDo(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new arguments[TEXT_FUNCTION_ARGUMENT];
    
  ReadAmxMemoryArray(argumentIdx, arguments);

  if (isnull(arguments)) {
    return SendMissCBMessage(playerid, blockid, actionid, "string");
  }

  if(!cmBlock[world][blockid][cbMode]) {
		cmd_do(playerid, arguments);
		return true;
	}

  foreach(new targetid : Player) {
    if(!cbCompareMode(targetid, blockid, world)) {
      continue;
    }

    cmd_do(targetid, arguments);
  }


  return true;
}

CB:ActionTry(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new arguments[TEXT_FUNCTION_ARGUMENT];
    
  ReadAmxMemoryArray(argumentIdx, arguments);

  if (isnull(arguments)) {
    return SendMissCBMessage(playerid, blockid, actionid, "string");
  }

  if(!cmBlock[world][blockid][cbMode]) {
		cmd_try(playerid, arguments);
		return true;
	}

  foreach(new targetid : Player) {
    if(!cbCompareMode(targetid, blockid, world)) {
      continue;
    }

    cmd_try(targetid, arguments);
  }


  return true;
}

CB:ChangePame(const playerid, const blockid, const actionid, const world, const argumentIdx) {
  new slot,
      str[142],
      arguments[TEXT_FUNCTION_ARGUMENT];
    
  ReadAmxMemoryArray(argumentIdx, arguments);

  if (sscanf(arguments, "ds[142]", slot, str)) {
    return SendMissCBMessage(playerid, blockid, actionid, "slot string");
  }

  if (1 > slot > 10) {
    return SendErrorCBMessage(playerid, blockid, actionid, "slot", "1-10");
  }
  slot--;

  if(!cmBlock[world][blockid][cbMode]) {
	strdel(pData[playerid][pPame], slot * 144, (slot + 1) * 144);
    strins(pData[playerid][pPame], str, slot * 144);
		return true;
	}

  foreach(new targetid : Player) {
    if(!cbCompareMode(targetid, blockid, world)) {
      continue;
    }

	strdel(pData[targetid][pPame], slot * 144, (slot + 1) * 144);
    strins(pData[targetid][pPame], str, slot * 144);
  }


  return true;
}

CB:specPlayerTarget(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
        arguments[TEXT_FUNCTION_ARGUMENT],
        targetid,
        userid;
    
    ReadAmxMemoryArray(argumentIdx, arguments);

    if(sscanf(arguments, "dD(-1)D(-1)", targetid, userid)) {
        return SendMissCBMessage(playerid, blockid, actionid, "targetid *playerid");
    }

    targetid = resolveTargetOrSelf(targetid, playerid);
    userid = resolveTargetOrSelf(userid, playerid);

    TogglePlayerSpectating(userid, true);
    PlayerSpectatePlayer(userid, targetid);
    SetPlayerInterior(userid, GetPlayerInterior(targetid) );

    return true;
}

CB:setPlyWorldBounds(const playerid, const blockid, const actionid, const world, const argumentIdx) {
    new
        arguments[TEXT_FUNCTION_ARGUMENT],
        userid;

    new
        Float:x_max, Float:x_min,
        Float:y_max, Float:y_min;

    ReadAmxMemoryArray(argumentIdx, arguments);

    if(sscanf(arguments, "dD(-1)ffff", userid, x_max, x_min, y_max, y_min)) {
        return SendMissCBMessage(playerid, blockid, actionid, "playerid x_max x_min y_max y_min");
    }

    userid = resolveTargetOrSelf(userid, playerid);

    SetPlayerWorldBounds(userid, x_max, x_min, y_max, y_min);
    return true;
}
