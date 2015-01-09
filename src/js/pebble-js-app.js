var load = 0;
var account_id = localStorage.getItem('account_id');
var region = localStorage.getItem('region');

function HTTPGET(url) {
	var req = new XMLHttpRequest();
	req.open("GET", url, false);
	req.send(null);
	if (req.status = 200) {
		load = 1;
		return req.responseText;
	};
}

var getData = function() {

    var tld			= '';
    var app_id      = '';
    var app_id_ru   = "";
    var app_id_asia = "";
    var app_id_kr   = "";
    var app_id_eu   = "";
    var app_id_com  = "";

    switch(region) {
      case '1':
        tld = "ru";
        app_id = app_id_ru;
        break;
      case '2':
        tld = "asia";
        app_id = app_id_asia;
        break;
      case '3':
        tld = "kr";
        app_id = app_id_kr;
        break;
      case '4':
        tld = "eu";
        app_id = app_id_eu;
        break;
      case '5':
        tld = "com";
        app_id = app_id_com;
        break;
    }

	var response = HTTPGET("https://api.worldoftanks." + tld + "/wot/account/info/?application_id=" + app_id + "&account_id=" + account_id);
	
	var json = JSON.parse(response);

	var nickname 				= json.data[account_id].nickname;
	var personal_rating 		= json.data[account_id].global_rating;
	var battles_fought 			= json.data[account_id].statistics["all"].battles;
	var wins 					= json.data[account_id].statistics["all"].wins;
	var wins_pct 				= (wins / battles_fought * 100).toFixed(2);
	var battles_survived 		= json.data[account_id].statistics["all"].survived_battles;
	var battles_survived_pct 	= (battles_survived / battles_fought * 100).toFixed(2);
	var total_xp 				= json.data[account_id].statistics["all"].xp;
	var avg_xp 					= json.data[account_id].statistics["all"].battle_avg_xp;
	var max_xp 					= json.data[account_id].statistics["max_xp"];
	var vehicles_destroyed 		= json.data[account_id].statistics["all"].frags;
	var vehicles_spotted 		= json.data[account_id].statistics["all"].spotted;
	var damage_caused 			= json.data[account_id].statistics["all"].damage_dealt;
	var hit_ratio 				= json.data[account_id].statistics["all"].hits_percents;
	var penetration_ratio 		= (json.data[account_id].statistics["all"].piercings / json.data[account_id].statistics["all"].shots * 100).toFixed(2);
	var avg_damage_blocked 		= json.data[account_id].statistics["all"].avg_damage_blocked;
	var armor_use_efficiency 	= json.data[account_id].statistics["all"].tanking_factor;
	var capture_points			= json.data[account_id].statistics["all"].capture_points;
	var defense_points			= json.data[account_id].statistics["all"].dropped_capture_points;	

	var dict = {"KEY_OK"					: load,
				"KEY_NICKNAME"				: nickname,
				"KEY_PERSONAL_RATING"		: personal_rating.toString(),
				"KEY_BATTLES_FOUGHT"		: battles_fought.toString(),
				"KEY_VICTORIES"				: wins_pct + "% / " + wins,
				"KEY_BATTLES_SURVIVED"		: battles_survived_pct + "% / " + battles_survived,
				"KEY_TOTAL_XP"				: total_xp.toString(),
				"KEY_AVG_XP"				: avg_xp.toString(),
				"KEY_MAXIMUM_XP"			: max_xp.toString(),
				"KEY_VEHICLES_DESTROYED"	: vehicles_destroyed.toString(),
				"KEY_VEHICLES_SPOTTED"		: vehicles_spotted.toString(),
				"KEY_DAMAGE_CAUSED"			: damage_caused.toString(),
				"KEY_HIT_RATIO"				: hit_ratio + "%",
				"KEY_PENETRATION_RATIO"		: penetration_ratio + "%",
				"KEY_AVG_DAMAGE_BLOCKED" 	: avg_damage_blocked.toString(),
				"KEY_ARMOR_USE_EFFICIENCY" 	: armor_use_efficiency.toString(),
				"KEY_CAPTURE_POINTS"		: capture_points.toString(),
				"KEY_DEFENSE_POINTS"		: defense_points.toString()
				};

	Pebble.sendAppMessage(dict);
};

Pebble.addEventListener("showConfiguration",
  function(e) {
    Pebble.openURL("http://kropochev.com/pebble/wot_adjutant/index_1.2.html");
  }
);

Pebble.addEventListener("webviewclosed",
  function(e) {
    options = JSON.parse(decodeURIComponent(e.response));
    localStorage.setItem('account_id', JSON.stringify(options.account_id));
    localStorage.setItem('region', JSON.stringify(options.region));
  }
);

Pebble.addEventListener("ready", function(e) {
		"use strict";
		getData();
});