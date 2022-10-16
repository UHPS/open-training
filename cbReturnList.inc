		/*
			��������� ������� ���������� � ������ ��������:
			playerid - ID ������
			params[] - ����� ���������� �� ��
			world - ������� ��� � ������� ��������� �����

			��������� ������ ���� ������� � str

			�������������� ����������:
			str[144]
			arg[32]
			userid = INVALID_PLAYER_ID (65535)
		*/


		if(!strcmp(str, "random", true))
		{
			if(!sscanf(arg, "p<,>dd", arg[0], arg[1]))
				valstr(str, RandomEx(arg[0], arg[1]));
			else
				continue;
		}
		else if(!strcmp(str, "array", true))
		{
			if(sscanf(arg, "d", arg[0]))
				continue;

			if(arg[0] < 0 || arg[0] > 26)
				continue;

			valstr(str, pData[playerid][cbData][ arg[0] ]);
		}
		else if(!strcmp(str, "server", true))
		{
			if(sscanf(arg, "d", arg[0]))
				continue;

			if(arg[0] < 0 || arg[0] > 51)
				continue;

			valstr(str, VW[world][vArray][ arg[0] ]);
		}
		else if(!strcmp(str, "var", true))
		{
			new
				var[32],
				data[MAX_VAR_DATA_LEN];

			if(sscanf(arg, "s[32]", var))
				continue;

			if(getVarData(playerid, var, data) == INVALID_VECTOR_INDEX)
				continue;

			format(str, sizeof(str), "%s", data);
			//valstr(str, pData[playerid][cbData][ arg[0] ]);
		}
		else if(!strcmp(str, "pvar", true))
		{
			new
				var[32],
				data[MAX_VAR_DATA_LEN];

			if(sscanf(arg, "p<,>s[32]d", var, userid))
				userid = playerid;

			if(!IsPlayerOnline(userid))
				continue;

			if(getPlayerVarData(userid, var, data) == INVALID_VECTOR_INDEX)
				continue;

			format(str, sizeof(str), "%s", data);
			//valstr(str, pData[playerid][cbData][ arg[0] ]);
		}
		else if(!strcmp(str, "vdata", true))
		{
			if(sscanf(arg, "dd", arg[0], arg[1]))
				continue;

			if(!IsValidVehicle(arg[0]))
			{
				if(!IsPlayerInAnyVehicle(playerid))
					continue;

				arg[0] = GetPlayerVehicleID(playerid);
			}

			if(arg[1] < 0 || arg[1] > 50)
				continue;

			valstr(str, vData[ arg[0] ][vArray][ arg[1] ]);
		}
		/*else if(!strcmp(str, "sscanf", true))
		{
			new context[64];
			if(sscanf(arg, "s[0]ds[64]", arg[0], arg[1], context))
				continue;

			new
				slenght = strlen(context),
				number,
				swh[24][64];

			for(new indx; indx < slenght; indx ++)
			{
				if(context[indx] == arg[0])
				{
					format(swh[indx], context[indx], "%s", context[number]);
					number ++;
				}
				if(number == arg[1])
				{
					format(str, sizeof(str), "%s", swh[number]);
					break;
				}
			}

		}*/
		else if(!strcmp(str, "array", true))
		{
			if(sscanf(arg, "d", arg[0]))
				continue;

			if(arg[0] < 0 || arg[0] > 26)
				continue;

			valstr(str, pData[playerid][cbData][ arg[0] ]);
		}
		else if(!strcmp(str, "teamOnline", true))
		{
			if(sscanf(arg, "d", arg[0]))
				continue;

			if(arg[0] < 1 || arg[0] > 20)
				continue;

			arg[0]--;
			new teamCount;
			foreach(new t : Player)
			{
				if(GetPlayerVirtualWorld(t) != world)
					continue;

				if(pData[t][pTeam] != arg[0])
					continue;

				teamCount++;
			}

			valstr(str, teamCount);
		}
		else if(!strcmp(str, "online", true))
		{
			new onlineCount;
			foreach(new t : Player)
			{
				if(GetPlayerVirtualWorld(t) != world)
					continue;

				onlineCount++;
			}

			valstr(str, onlineCount);
		}
		else if(!strcmp(str, "anim", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, GetPlayerAnimationIndex(userid));
		}
		else if(!strcmp(str, "skin", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pSkin]);
		}
		else if(!strcmp(str, "acid", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pID]);
		}
		else if(!strcmp(str, "gun", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, GetPlayerWeapon(userid));
		}
		else if(!strcmp(str, "ammo", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, dgun[playerid][ammo_slot][ getGunSlot( GetPlayerWeapon(userid) ) ]);
		}
		else if(!strcmp(str, "vehicle", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, GetPlayerVehicleID(userid));
		}
		else if(!strcmp(str, "timestamp", true))
		{
			valstr(str, gettime() - 1577836800);
		}
		else if(!strcmp(str, "team", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pTeam] + 1);
		}
		else if(!strcmp(str, "score", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, GetPlayerScore(userid));
		}
		else if(!strcmp(str, "money", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pMoney]);
		}
		else if(!strcmp(str, "health", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			format(str, sizeof(str), " %.1f", pData[userid][pHealth]);
		}
		else if(!strcmp(str, "armour", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			format(str, sizeof(str), " %.1f", pData[userid][pArmour]);
		}
		else if(!strcmp(str, "playerid", true))
		{
			valstr(str, playerid);
		}
		else if(!strcmp(str, "name", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			GetPlayerName(userid, str, sizeof(str));
		}
		else if(!strcmp(str, "xyz", true))
		{
			new
				Float:x,
				Float:y,
				Float:z;

			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			GetPlayerPos(userid, x, y, z);
			format(str, sizeof(str), "%.1f %.1f %.1f", x, y, z);
		}
		else if(!strcmp(str, "x", true))
		{
			new
				Float:x,
				Float:y,
				Float:z;

			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			GetPlayerPos(userid, x, y, z);
			format(str, sizeof(str), " %.1f", x);
		}
		else if(!strcmp(str, "y", true))
		{
			new
				Float:x,
				Float:y,
				Float:z;

			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			GetPlayerPos(userid, x, y, z);
			format(str, sizeof(str), " %.1f", y);
		}
		else if(!strcmp(str, "z", true))
		{
			new
				Float:x,
				Float:y,
				Float:z;

			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			GetPlayerPos(userid, x, y, z);
			format(str, sizeof(str), "%.1f", z);
		}
		else if(!strcmp(str, "speed", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			if(IsPlayerInAnyVehicle(userid))
				format(str, sizeof(str), "%d", floatround(Vehicle_Speed( GetPlayerVehicleID(userid) )));
			else
				format(str, sizeof(str), "%d", floatround(GetPlayerSpeed(userid)));
		}
		else if(!strcmp(str, "vehName", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			if(IsPlayerInAnyVehicle(userid))
				ReturnVehicleNameEx(GetPlayerVehicleID(userid), str);
			else
				format(str, sizeof(str), "N/A");
		}
		else if(!strcmp(str, "vehHealth", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			if(IsPlayerInAnyVehicle(userid))
			{
				new Float:health;
				GetVehicleHealth(GetPlayerVehicleID(userid), health);
				format(str, sizeof(str), " %.1f", health);
			}
		}
		else if(!strcmp(str, "vehColor", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			if(IsPlayerInAnyVehicle(userid))
			{
				new
					color1,
					color2;

				GetVehicleColor(GetPlayerVehicleID(userid), color1, color2);
				format(str, sizeof(str), "%s", VehicleColoursTableRGB[color1]);
			}
		}
		else if(!strcmp(str, "gunName", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			GetWeaponName(GetPlayerWeapon(userid), str, sizeof(str));
		}
		else if(!strcmp(str, "time", true))
		{
			valstr(str, VW[world][vTime]);
		}
		else if(!strcmp(str, "weather", true))
		{
			valstr(str, VW[world][vWeather]);
		}
		else if(!strcmp(str, "wanted", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, GetPlayerWantedLevel(userid));
		}
		else if(!strcmp(str, "drunk", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, GetPlayerDrunkLevel(userid));
		}
		else if(!strcmp(str, "channel", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pChannel]);
		}
		else if(!strcmp(str, "bodypart", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pTakeDamageBPart]);
		}
		else if(!strcmp(str, "issuerGun", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pTakeDamageWeapon]);
		}
		else if(!strcmp(str, "attach", true))
		{
			if(sscanf(arg, "dD(-1)", arg[0], arg[1]))
				continue;

			if(arg[0] < 1 || arg[0] > 10)
				continue;

			if(!IsPlayerOnline(arg[1]))
				playerid = arg[1];

			arg[0]--;
			valstr(str, pAttach[playerid][ arg[0] ][0]);
		}
		else if(!strcmp(str, "retval", true))
		{
			if(sscanf(arg, "dD(-1)", arg[0], arg[1]))
				continue;

			if(arg[0] < 0 || arg[0] > 9)
				continue;

			if(IsPlayerOnline(arg[1]))
				playerid = arg[1];

			valstr(str, pData[playerid][pRetVal][ arg[0] ]);
		}
		else if(!strcmp(str, "retstr", true))
		{
			sscanf(arg, "D(-1)D(-1)", arg[0], arg[1]);

			if(arg[0] == -1)
			{
				if(IsPlayerOnline(arg[1]))
					playerid = arg[1];

				format(str, sizeof(str), "%s", pData[playerid][pRetStr]);
			}
			else
			{
				if(arg[0] < 0 || arg[0] > 9)
					continue;

				if(IsPlayerOnline(arg[1]))
					playerid = arg[1];

				format(str, sizeof(str), "%.24s", pData[playerid][pRetStr][ arg[0] * 24 ]);
			}
		}
		else if(!strcmp(str, "GetPlayerName", true))
		{
			sscanf(arg, "d", arg[0]);
			if(!IsPlayerOnline(arg[0]))
				arg[0] = playerid;

			if(arg[0] < 0 || arg[0] > MAX_PLAYERS)
				continue;

			GetPlayerName(arg[0], str, sizeof(str));
		}
		else if(!strcmp(str, "GetVehName", true))
		{
			if(sscanf(arg, "d", arg[0]))
				continue;

			ReturnVehicleNameEx(arg[0], str);
		}
		else if(!strcmp(str, "GetDist", true))
		{
			new Float:x[2], Float:y[2], Float:z[2];

			if(sscanf(arg, "p<,>ffffff", x[0], y[0], z[0], x[1], y[1], z[1]))
				continue;

			format(str, sizeof(str), "%.2f", VectorSize(x[0] - x[1], y[0] - y[1], z[0] - z[1]) );
		}
		else if(!strcmp(str, "GetDistPlayer", true))
		{
			if(sscanf(arg, "dD(-1)", arg[0], arg[1]))
				continue;

			if(IsPlayerOnline(arg[1]))
				playerid = arg[1];

			valstr(str, floatround(GetPlayerDistanceFromPlayer(playerid, arg[0])));
		}
		else if(!strcmp(str, "GetDistPos", true))
		{
			new
				Float:x,
				Float:y,
				Float:z;

			if(sscanf(arg, "fff", x, y, z))
				continue;

			valstr(str, floatround(GetPlayerDistanceFromPoint(playerid, x, y, z)));
		}
		else if(!strcmp(str, "GetFAPlayer", true))
		{
			sscanf(arg, "d", arg[0]);
			if(!IsPlayerOnline(arg[0]))
				arg[0] = playerid;

			new Float:Angle;
			GetPlayerFacingAngle(arg[0], Angle);

			valstr(str, floatround(Angle));
		}
		else if(!strcmp(str, "GetDistVeh", true))
		{
			if(sscanf(arg, "dD(-1)", arg[0], arg[1]))
				continue;

			if(arg[0] < 0 || arg[0] > MAX_WORLD_VEHICLE)
				continue;

			if(IsPlayerOnline((arg[1])))
				playerid = arg[1];

			valstr(str, floatround(GetPlayerDistanceFromVehicle(playerid, tempWorld[world][vehSlot][ arg[0] ])));
		}
		else if(!strcmp(str, "GetDistObject", true))
		{
			if(sscanf(arg, "dD(-1)", arg[0], arg[1]))
				continue;

			if(IsPlayerOnline((arg[1])))
				playerid = arg[1];

			valstr(str, floatround(GetPlayerDistanceFromObject(playerid, arg[0])));
		}
		else if(!strcmp(str, "VehModel", true))
		{
			sscanf(arg, "d", userid);
			if(userid == INVALID_PLAYER_ID)
				userid = playerid;

			if(IsPlayerInAnyVehicle(playerid))
				valstr(str, GetVehicleModel(GetPlayerVehicleID(playerid)));
		}
		else if(!strcmp(str, "passinfo", true))
		{
			sscanf(arg, "d", userid);
			if(userid == INVALID_PLAYER_ID)
				userid = playerid;

			new data[2];
			Streamer_GetArrayData(STREAMER_TYPE_PICKUP, pData[userid][pPickup], E_STREAMER_EXTRA_ID, data);
			arg[0] = data[0];
			pData[userid][pPickup] = false;

			if(data[1] == 1)
			{
				if(IsPlayerInRangeOfPoint(playerid, 3.0, passData[world][ arg[0] ][pExitPosX], passData[world][ arg[0] ][pExitPosY], passData[world][ arg[0] ][pExitPosZ]))
					valstr(str, arg[0]);
			}
			else
			{
				if(IsPlayerInRangeOfPoint(playerid, 3.0, passData[world][ arg[0] ][pEnterPosX], passData[world][ arg[0] ][pEnterPosY], passData[world][ arg[0] ][pEnterPosZ]))
					valstr(str, arg[0]);
			}
		}
		else if(!strcmp(str, "getvehmodel", true))
		{
			sscanf(arg, "d", arg[0]);
			format(str, sizeof(str), "%s", ReturnVehicleName(arg[0], 1));
		}
		else if(!strcmp(str, "vehpos", true))
		{
			sscanf(arg, "d", arg[0]);

			if(!IsValidVehicle(arg[0]))
				continue;

			if(GetVehicleVirtualWorld(arg[0]) != world)
				continue;

			new
				Float:x,
				Float:y,
				Float:z;

			GetVehiclePos(arg[0], x, y, z);
			format(str, sizeof(str), "%.1f %.1f %.1f", x, y, z);
		}
		else if(!strcmp(str, "vehseat", true))
		{
			sscanf(arg, "u", userid);
			if(userid == INVALID_PLAYER_ID)
				userid = playerid;

			valstr(str, GetPlayerVehicleSeat(userid));
		}
		else if(!strcmp(str, "waterlvl", true))
		{
			new
				Float:depth,
				Float:playerdepth;

			sscanf(arg, "u", userid);
			if(userid == INVALID_PLAYER_ID)
				userid = playerid;

			CA_IsPlayerInWater(userid, depth, playerdepth);
			format(str, sizeof(str), "%.1f", playerdepth);
		}
		else if(!strcmp(str, "getDistAction", true))
		{
			new
				actionId,
				Float:x, Float:y, Float:z;

			sscanf(arg, "d", actionId);

			if(!checkValidAction(actionId, world))
				continue;

			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_X, x);
			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_Y, y);
			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_Z, z);

			new Float:distance = GetPlayerDistanceFromPoint(playerid, x, y, z);
			format(str, sizeof(str), "%.2f", distance);
		}
		else if(!strcmp(str, "floatnum", true)) {
			new Float: num[2], type, Float: numRes;
			if (sscanf(arg, "fdf", num[0], type, num[1])) {
				continue;
			}

			switch (type) {
				case 0: {
					numRes = num[0] + num[1];
				}
				case 1: {
					numRes = num[0] - num[1];
				}
				case 2: {
					numRes = num[0] * num[1];
				}
				case 3: {
					numRes = num[0] / num[1];
				}
			}

			format(str, sizeof(str), "%.4f", numRes);
		}
		else if(!strcmp(str, "omodel", true))
		{
			new objectid,
				modelid;

			if(sscanf(arg, "d", objectid))
				continue;

			objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
			if(objectid <= 0)
				continue;

			modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID);

			valstr(str, modelid);
		}
		else if(!strcmp(str, "oArray", true)) {
			new objectid;
			if (sscanf(arg, "d", objectid)) {
				continue;
			}

			objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
			if(objectid <= 0)
				continue;

			valstr(str, Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_CUSTOM(1237)) );
		}
		else if(!strcmp(str, "oStatus", true))
		{
			new objectid;
			if(sscanf(arg, "d", objectid))
				continue;

			objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
			if(objectid <= 0)
				continue;

			valstr(str, Streamer_IsToggleItem(-1, STREAMER_TYPE_OBJECT, objectid));
		}
		else if(!strcmp(str, "oXYZ", true))
		{
			new objectid,
				Float:x,
				Float:y,
				Float:z;

			if(sscanf(arg, "d", objectid))
				continue;

			objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
			if(objectid <= 0)
				continue;

			GetDynamicObjectPos(objectid, x, y, z);

			format(str, sizeof(str), "%.2f %.2f %.2f", x, y, z);
		}
		else if(!strcmp(str, "oX", true))
		{
			new objectid,
				Float:cord;

			if(sscanf(arg, "d", objectid))
				continue;

			objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
			if(objectid <= 0)
				continue;

			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, cord);

			format(str, sizeof(str), "%.2f", cord);
		}
		else if(!strcmp(str, "oY", true))
		{
			new objectid,
				Float:cord;

			if(sscanf(arg, "d", objectid))
				continue;

			objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
			if(objectid <= 0)
				continue;

			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, cord);

			format(str, sizeof(str), "%.2f", cord);
		}
		else if(!strcmp(str, "oZ", true))
		{
			new objectid,
				Float:cord;

			if(sscanf(arg, "d", objectid))
				continue;

			objectid = VECTOR_get_val(WorldObjectSystem[world][wosObject], objectid);
			if(objectid <= 0)
				continue;

			Streamer_GetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, cord);

			format(str, sizeof(str), "%.2f", cord);
		}
		else if(!strcmp(str, "actionXYZ", true))
		{
			new
				actionId,
				Float:x, Float:y, Float:z;

			sscanf(arg, "d", actionId);

			if(!checkValidAction(actionId, world))
				continue;

			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_X, x);
			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_Y, y);
			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_Z, z);

			format(str, sizeof(str), "%.2f %.2f %.2f", x, y, z);
		}
		else if(!strcmp(str, "actionX", true))
		{
			new
				actionId, Float:cord;

			sscanf(arg, "d", actionId);

			if(!checkValidAction(actionId, world))
				continue;

			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_X, cord);

			format(str, sizeof(str), "%.2f", cord);
		}
		else if(!strcmp(str, "actionY", true))
		{
			new
				actionId, Float:cord;

			sscanf(arg, "d", actionId);

			if(!checkValidAction(actionId, world))
				continue;

			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_Y, cord);

			format(str, sizeof(str), "%.2f", cord);
		}
		else if(!strcmp(str, "actionZ", true))
		{
			new
				actionId, Float:cord;

			sscanf(arg, "d", actionId);

			if(!checkValidAction(actionId, world))
				continue;

			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,
				Text3D:worldAction[world][actionId][vAction], E_STREAMER_Z, cord);

			format(str, sizeof(str), "%.2f", cord);
		}
		else if(!strcmp(str, "nearveh", true))
		{
			new type;
			sscanf(arg, "d", type);

			if(IsPlayerInAnyVehicle(playerid) && !type)
			{
				arg[0] = GetPlayerVehicleID(playerid);
			}
			else
			{
				new
					Float:radius,
					Float:x,
					Float:y,
					Float:z;

				if(type)
				{
					type = false;
					if(IsPlayerInAnyVehicle(playerid))
						type = GetPlayerVehicleID(playerid);
				}

				GetPlayerPos(playerid, x, y, z);

				for(new vehicleid; vehicleid <= GetVehiclePoolSize(); vehicleid++)
				{
					if(!IsValidVehicle(vehicleid))
						continue;

					if(GetVehicleVirtualWorld(vehicleid) != world)
						continue;

					if(type == vehicleid)
						continue;

					new Float:tempRadius = GetVehicleDistanceFromPoint(vehicleid, x, y, z);

					if(tempRadius > 3.2)
						continue;

					if(radius != 0.0 && tempRadius > radius)
						continue;

					radius = tempRadius;
					arg[0] = vehicleid;
				}
			}

			valstr(str, arg[0]);
		}
		/*else if(!strcmp(str, "nearobj", true))
		{
			new
				Float:x[2], Float:y[2], Float:z[2],
				Float:range,
				items[10];

			sscanf(arg, "F(3)", range);

			if(range < 0)
				range = 3;

			if(range > 200)
				range = 200;

			GetPlayerPos(playerid, x[0], y[0], z[0]);
			Streamer_GetNearbyItems(x[0], y[0], z[0], STREAMER_TYPE_OBJECT, items, sizeof(items), range, GetPlayerVirtualWorld(playerid));

			for(new obj; obj < sizeof(items); obj ++)
			{
				new val = Streamer_GetIntData(STREAMER_TYPE_OBJECT, items[obj], E_STREAMER_EXTRA_ID);
				printf("items[obj] = %d | val: %d", items[obj], val);

				if(items[obj] == 0)
					continue;

				GetDynamicObjectPos(items[obj], x[1], y[1], z[1]);
				new Float:tempRadius = VectorSize(x[0] - x[1], y[0] - y[1], z[0] - z[1]);
				if(tempRadius > range)
					continue;
			}
		}*/
		else if(!strcmp(str, "isWorld", true))
		{
			sscanf(arg, "D(-1)", arg[0]);

			if(GetPlayerVirtualWorld(arg[0]) == GetPlayerVirtualWorld(playerid))
				format(str, sizeof(str), "1");
			else
				format(str, sizeof(str), "0");
		}
		else if(!strcmp(str, "GetGunName", true))
		{
			sscanf(arg, "d", arg[0]);
			if(!IsPlayerOnline(arg[0]))
				arg[0] = playerid;

			GetWeaponName(arg[0], str, sizeof(str));
		}
		else if(!strcmp(str, "zone", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			GetPlayer2DZone(userid, str, MAX_ZONE_NAME);
		}
		else if(!strcmp(str, "getzone", true))
		{
			new
				Float:x,
				Float:y;

			sscanf(arg, "ff", x, y);
			Get2DZone(x, y, str, MAX_ZONE_NAME);
		}
		else if(!strcmp(str, "getzoneid", true))
		{
			new
				Float:x,
				Float:y;

			sscanf(arg, "ff", x, y);
			valstr(str, Get2DZoneId(x, y));
		}
		else if(!strcmp(str, "ping", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, GetPlayerPing(userid));
		}
		else if(!strcmp(str, "ban", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			if(pData[userid][pBanned])
				valstr(str, 1);
			else
				valstr(str, 0);
		}
		else if(!strcmp(str, "vmute", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			new time = pData[userid][pWorldMute] - gettime();
			if(time < gettime())
				time = 0;

			valstr(str, time);
		}
		else if(!strcmp(str, "netstat", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			format(str, sizeof(str), " %.1f", NetStats_PacketLossPercent(userid));
		}
		else if(!strcmp(str, "hr", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			format(str, sizeof(str), " %d", (100 * pData[userid][pHit])/pData[userid][pShot]);
		}
		else if(!strcmp(str, "randomPlayer", true))
		{
			new
				category[24],
				categoryType,
				type[2],
				playerCount = -1,
				playerList[500];

			sscanf(arg, "s[24]D(0)D(0)", category, type[0], type[1]);

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
				valstr(str, playerList[ RandomEx(0, playerCount) ]);
			else
				valstr(str, 0);
		}
		else if(!strcmp(str, "front", true)) {
			new Float: x, Float: y, Float:z, Float: angle, Float: dist, type;
			if(sscanf(arg, "fD(-1)", dist, type)) {
				continue;
			}

			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);

			x += dist * floatsin(-angle, degrees);
			y += dist * floatcos(-angle, degrees);

			switch(type) {
				case 0: format(str, sizeof(str), "%.4f", x);
				case 1: format(str, sizeof(str), "%.4f", y);
				default: format(str, sizeof(str), "%.4f %.4f", x, y);
			}
		}
		else if(!strcmp(str, "raycast", true))
		{
			new
				Float:pX, Float:pY, Float:pZ,
				Float:vX, Float:vY, Float:vZ,
				Float:atX, Float:atY, Float:atZ,
				category[24], coord[4];

			sscanf(arg, "s[24]D(30)D(0)s[4]", category, arg[0], arg[1], coord);

			if(isnull(coord))
				format(coord, sizeof(coord), "xyz");

			if(!strcmp(category, "cam", true))
			{
				GetPlayerCameraPos(playerid, pX, pY, pZ);
				GetPlayerCameraFrontVector(playerid, vX, vY, vZ);

				vX = pX + (vX * arg[0]);
				vY = pY + (vY * arg[0]);
				vZ = pZ + (vZ * arg[0]);

				CA_RayCastLine(pX, pY, pZ, vX, vY, vZ, atX, atY, atZ);
			}
			else if(!strcmp(category, "pos", true))
			{
				if(IsPlayerInAnyVehicle(playerid))
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					GetVehiclePos(vehicleid, pX, pY, pZ);
					GetVehicleRotation(vehicleid, vX, vY, vZ);

					atX = pX + (arg[0] * floatsin(-vZ, degrees)),
					atY = pY + (arg[0] * floatcos(-vZ, degrees)),
					atZ = pZ + (arg[0] * floatsin(vX, degrees));

					CA_RayCastLine(pX, pY, pZ, atX, atY, atZ, atX, atY, atZ);
				}
				else
				{
					GetPlayerPos(playerid,  pX, pY, pZ);
					GetPlayerFacingAngle(playerid, vZ);

					vX = pX + (arg[0]*floatsin(-vZ, degrees));
					vY = pY + (arg[0]*floatcos(-vZ, degrees));

					CA_RayCastLine(pX, pY, pZ, vX, vY, pZ, atX, atY, atZ);
				}
			}

			if(arg[1] == 1)
			{
				if(atX == 0.0 && atY == 0.0 && atZ == 0.0)
					format(str, sizeof(str), "%.1f %.1f %.1f", vX, vY, pZ);
				else
					format(str, sizeof(str), "%.1f %.1f %.1f", atX, atY, atZ);
			}
			else
			{
				format(str, sizeof(str), "%.1f %.1f %.1f", atX, atY, atZ);
			}

			new Float:cX, Float:cY, Float:cZ;

			if(sscanf(str, "fff", cX, cY, cZ))
				continue;

			if(!strcmp(coord, "x"))
				format(str, sizeof(str), "%.1f", cX);
			else if(!strcmp(coord, "y"))
				format(str, sizeof(str), "%.1f", cY);
			else if(!strcmp(coord, "z"))
				format(str, sizeof(str), "%.1f", cZ);
			else
				format(str, sizeof(str), "%.1f %.1f %.1f", cX, cY, cZ);
		}
		else if(!strcmp(str, "getZ", true))
		{
			new
				Float:FLOAT_NONE,
				Float:x,
				Float:y,
				Float:z;

			if(sscanf(arg, "ff", x, y))
				continue;

			if(!CA_RayCastLine(x, y, 600.0, x, y, -100, FLOAT_NONE, FLOAT_NONE, z))
				z = 0.0;

			format(str, sizeof(str), " %.1f", z);
		}
		else if(!strcmp(str, "fa", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			new Float:angle;

			if(IsPlayerInAnyVehicle(userid))
				GetVehicleZAngle(GetPlayerVehicleID(userid), angle);
			else
				GetPlayerFacingAngle(userid, angle);

			format(str, sizeof(str), " %.1f", angle);
		}
		else if(!strcmp(str, "afk", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pAFK]);
		}
		else if(!strcmp(str, "death", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, pData[userid][pDeadStage]);
		}
		else if(!strcmp(str, "target", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			valstr(str, GetPlayerTargetPlayer(userid));
		}
		else if(!strcmp(str, "getFA", true))
		{
			if(sscanf(arg, "ddD(-1)", arg[0], arg[1], arg[2]))
				continue;

			if(IsPlayerOnline(arg[2]))
				playerid = arg[2];

			new
				Float:x,
				Float:y,
				Float:z,
				Float:angle;

			GetPlayerPos(playerid, x, y, z);
			angle = 180.0-atan2(arg[0]-x, arg[1]-y);
			format(str, sizeof(str), " %.1f", angle);
		}
		else if(!strcmp(str, "teamName", true))
		{
			if(sscanf(arg, "d", userid))
				userid = playerid;

			if(GetPlayerVirtualWorld(userid) != world)
				userid = playerid;

			if(pData[userid][pTeam] < 0)
			{
				format(str, sizeof(str), "N/A");
			}
			else
			{
				format(str, sizeof(str), "%s", worldTeam[world][ pData[userid][pTeam] ][tName]);
			}

		}
		else if(!strcmp(str, "strlen", true))
		{
			valstr(str, strlen(arg));
		}
		else if(!strcmp(str, "ext", true))
		{
			if(sscanf(arg, "dd", arg[0], arg[1]))
				continue;

			if(arg[0] < 0 || arg[0] > VW[world][wMaxCB])
				continue;

			switch(arg[1])
			{
				case 1: StreamerBlockGetArray(cmBlock[world][ arg[0] ][cbID], 1, str, 144);
				case 2: StreamerBlockGetArray(cmBlock[world][ arg[0] ][cbID], 2, str, 144);
				case 3: StreamerBlockGetArray(cmBlock[world][ arg[0] ][cbID], 3, str, 144);
				case 4: StreamerBlockGetArray(cmBlock[world][ arg[0] ][cbID], 4, str, 144);
				case 5: StreamerBlockGetArray(cmBlock[world][ arg[0] ][cbID], 5, str, 144);
				default: continue;
			}
		}
		else if(!strcmp(str, "nearply", true))
		{
			sscanf(arg, "d", userid);
			if(!IsPlayerOnline(userid))
				userid = playerid;

			new	interiorid = GetPlayerInterior(userid);

			new	Float: X,
				Float: Y,
				Float: Z;

			new	lastData[2] = { cellmax, -1 };

			foreach(new player : Player) {

				if(!(GetPlayerVirtualWorld(player) == world && GetPlayerInterior(i) == interiorid) || player == userid)
															continue;

				if(GetPlayerPos(player, X, Y, Z) && (floatround(GetPlayerDistanceFromPoint(userid, X, Y, Z)) < lastData[0])) {

					lastData[0] = floatround(GetPlayerDistanceFromPoint(userid, X, Y, Z));
					lastData[1] = player;

				}
			}

			valstr(str, lastData[1]);
		}