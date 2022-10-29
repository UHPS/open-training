enum blockMethodList_enum
{
    cbm_has_params,
    cbm_folder_id,
    cbm_function[32],
    cbm_name[64],
    cbm_description[512]
}

new blockMethodFolders[][] = {
    "Общие параметры",
    "Массивы",
    "Транспорт",
    "Взаимодействие с игроком",
    "Чекпоинты",
    "Объекты мира",
    "Актеры"
};

new blockMethodList[][] = {
    {false, 0, "cb_setHealth", "Установить HP", "Установить HP игроку: 100.0"}
};