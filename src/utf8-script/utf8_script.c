#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

static struct option long_opts[] = {
  {"count-ascii", 0, NULL, 'c'},
  {"skip-ascii", 0, NULL, 's'},
  {0, 0, 0, 0}
};

enum unicode_script {
  adlam = 0,
  ahom = 1,
  anatolian_hieroglyphs = 2,
  arabic = 3,
  armenian = 4,
  avestan = 5,
  balinese = 6,
  bamum = 7,
  bassa_vah = 8,
  batak = 9,
  bengali = 10,
  bhaiksuki = 11,
  bopomofo = 12,
  brahmi = 13,
  braille = 14,
  buginese = 15,
  buhid = 16,
  canadian_aboriginal = 17,
  carian = 18,
  caucasian_albanian = 19,
  chakma = 20,
  cham = 21,
  cherokee = 22,
  chorasmian = 23,
  common = 24,
  coptic = 25,
  cuneiform = 26,
  cypriot = 27,
  cypro_minoan = 28,
  cyrillic = 29,
  deseret = 30,
  devanagari = 31,
  dives_akuru = 32,
  dogra = 33,
  duployan = 34,
  egyptian_hieroglyphs = 35,
  elbasan = 36,
  elymaic = 37,
  ethiopic = 38,
  garay = 39,
  georgian = 40,
  glagolitic = 41,
  gothic = 42,
  grantha = 43,
  greek = 44,
  gujarati = 45,
  gunjala_gondi = 46,
  gurmukhi = 47,
  gurung_khema = 48,
  han = 49,
  hangul = 50,
  hanifi_rohingya = 51,
  hanunoo = 52,
  hatran = 53,
  hebrew = 54,
  hiragana = 55,
  imperial_aramaic = 56,
  inherited = 57,
  inscriptional_pahlavi = 58,
  inscriptional_parthian = 59,
  javanese = 60,
  kaithi = 61,
  kannada = 62,
  katakana = 63,
  kawi = 64,
  kayah_li = 65,
  kharoshthi = 66,
  khitan_small_script = 67,
  khmer = 68,
  khojki = 69,
  khudawadi = 70,
  kirat_rai = 71,
  lao = 72,
  latin = 73,
  lepcha = 74,
  limbu = 75,
  linear_a = 76,
  linear_b = 77,
  lisu = 78,
  lycian = 79,
  lydian = 80,
  mahajani = 81,
  makasar = 82,
  malayalam = 83,
  mandaic = 84,
  manichaean = 85,
  marchen = 86,
  masaram_gondi = 87,
  medefaidrin = 88,
  meetei_mayek = 89,
  mende_kikakui = 90,
  meroitic_cursive = 91,
  meroitic_hieroglyphs = 92,
  miao = 93,
  modi = 94,
  mongolian = 95,
  mro = 96,
  multani = 97,
  myanmar = 98,
  nabataean = 99,
  nag_mundari = 100,
  nandinagari = 101,
  new_tai_lue = 102,
  newa = 103,
  nko = 104,
  nushu = 105,
  nyiakeng_puachue_hmong = 106,
  ogham = 107,
  ol_chiki = 108,
  ol_onal = 109,
  old_hungarian = 110,
  old_italic = 111,
  old_north_arabian = 112,
  old_permic = 113,
  old_persian = 114,
  old_sogdian = 115,
  old_south_arabian = 116,
  old_turkic = 117,
  old_uyghur = 118,
  oriya = 119,
  osage = 120,
  osmanya = 121,
  pahawh_hmong = 122,
  palmyrene = 123,
  pau_cin_hau = 124,
  phags_pa = 125,
  phoenician = 126,
  psalter_pahlavi = 127,
  rejang = 128,
  runic = 129,
  samaritan = 130,
  saurashtra = 131,
  sharada = 132,
  shavian = 133,
  siddham = 134,
  signwriting = 135,
  sinhala = 136,
  sogdian = 137,
  sora_sompeng = 138,
  soyombo = 139,
  sundanese = 140,
  sunuwar = 141,
  syloti_nagri = 142,
  syriac = 143,
  tagalog = 144,
  tagbanwa = 145,
  tai_le = 146,
  tai_tham = 147,
  tai_viet = 148,
  takri = 149,
  tamil = 150,
  tangsa = 151,
  tangut = 152,
  telugu = 153,
  thaana = 154,
  thai = 155,
  tibetan = 156,
  tifinagh = 157,
  tirhuta = 158,
  todhri = 159,
  toto = 160,
  tulu_tigalari = 161,
  ugaritic = 162,
  unknown = 163,
  vai = 164,
  vithkuqi = 165,
  wancho = 166,
  warang_citi = 167,
  yezidi = 168,
  yi = 169,
  zanabazar_square = 170,
};

char *scripts[] = {
  "Adlam",
  "Ahom",
  "Anatolian_Hieroglyphs",
  "Arabic",
  "Armenian",
  "Avestan",
  "Balinese",
  "Bamum",
  "Bassa_Vah",
  "Batak",
  "Bengali",
  "Bhaiksuki",
  "Bopomofo",
  "Brahmi",
  "Braille",
  "Buginese",
  "Buhid",
  "Canadian_Aboriginal",
  "Carian",
  "Caucasian_Albanian",
  "Chakma",
  "Cham",
  "Cherokee",
  "Chorasmian",
  "Common",
  "Coptic",
  "Cuneiform",
  "Cypriot",
  "Cypro_Minoan",
  "Cyrillic",
  "Deseret",
  "Devanagari",
  "Dives_Akuru",
  "Dogra",
  "Duployan",
  "Egyptian_Hieroglyphs",
  "Elbasan",
  "Elymaic",
  "Ethiopic",
  "Garay",
  "Georgian",
  "Glagolitic",
  "Gothic",
  "Grantha",
  "Greek",
  "Gujarati",
  "Gunjala_Gondi",
  "Gurmukhi",
  "Gurung_Khema",
  "Han",
  "Hangul",
  "Hanifi_Rohingya",
  "Hanunoo",
  "Hatran",
  "Hebrew",
  "Hiragana",
  "Imperial_Aramaic",
  "Inherited",
  "Inscriptional_Pahlavi",
  "Inscriptional_Parthian",
  "Javanese",
  "Kaithi",
  "Kannada",
  "Katakana",
  "Kawi",
  "Kayah_Li",
  "Kharoshthi",
  "Khitan_Small_Script",
  "Khmer",
  "Khojki",
  "Khudawadi",
  "Kirat_Rai",
  "Lao",
  "Latin",
  "Lepcha",
  "Limbu",
  "Linear_A",
  "Linear_B",
  "Lisu",
  "Lycian",
  "Lydian",
  "Mahajani",
  "Makasar",
  "Malayalam",
  "Mandaic",
  "Manichaean",
  "Marchen",
  "Masaram_Gondi",
  "Medefaidrin",
  "Meetei_Mayek",
  "Mende_Kikakui",
  "Meroitic_Cursive",
  "Meroitic_Hieroglyphs",
  "Miao",
  "Modi",
  "Mongolian",
  "Mro",
  "Multani",
  "Myanmar",
  "Nabataean",
  "Nag_Mundari",
  "Nandinagari",
  "New_Tai_Lue",
  "Newa",
  "Nko",
  "Nushu",
  "Nyiakeng_Puachue_Hmong",
  "Ogham",
  "Ol_Chiki",
  "Ol_Onal",
  "Old_Hungarian",
  "Old_Italic",
  "Old_North_Arabian",
  "Old_Permic",
  "Old_Persian",
  "Old_Sogdian",
  "Old_South_Arabian",
  "Old_Turkic",
  "Old_Uyghur",
  "Oriya",
  "Osage",
  "Osmanya",
  "Pahawh_Hmong",
  "Palmyrene",
  "Pau_Cin_Hau",
  "Phags_Pa",
  "Phoenician",
  "Psalter_Pahlavi",
  "Rejang",
  "Runic",
  "Samaritan",
  "Saurashtra",
  "Sharada",
  "Shavian",
  "Siddham",
  "SignWriting",
  "Sinhala",
  "Sogdian",
  "Sora_Sompeng",
  "Soyombo",
  "Sundanese",
  "Sunuwar",
  "Syloti_Nagri",
  "Syriac",
  "Tagalog",
  "Tagbanwa",
  "Tai_Le",
  "Tai_Tham",
  "Tai_Viet",
  "Takri",
  "Tamil",
  "Tangsa",
  "Tangut",
  "Telugu",
  "Thaana",
  "Thai",
  "Tibetan",
  "Tifinagh",
  "Tirhuta",
  "Todhri",
  "Toto",
  "Tulu_Tigalari",
  "Ugaritic",
  "Unknown",
  "Vai",
  "Vithkuqi",
  "Wancho",
  "Warang_Citi",
  "Yezidi",
  "Yi",
  "Zanabazar_Square"
};

void
usage(int exit_status) {
  fprintf(stderr, "USAGE: utf8-script [--count-ascii | --skip-ascii]\n");
  exit(exit_status);
}

int
main(int argc, char **argv) {
  wchar_t ch;
  size_t counts[171];
  int flag, flag_count = 0;
  char *endptr;
  bool count_ascii = false;
  size_t ascii_cnt = 0;
  bool skip_ascii = false;

  while (true) {
    flag = getopt_long(argc, argv, "cs", long_opts, NULL);
    if (-1 == flag)
      break;
    switch(flag) {
    case 'c':
      count_ascii = true;
      flag_count += 1;
      break;
    case 's':
      skip_ascii = true;
      flag_count += 1;
      break;
    default:
      usage(1);
    }
  } 

  if ( argc - flag_count > 1)
    usage(1);

  int i;
  for (i = 0; i < 171; ++i) {
    counts[i] = 0;
  }

  setlocale(LC_ALL, "");

  while ((ch = getwchar()) != WEOF) {
    if (skip_ascii && ch >= 0 && ch < 128)
      continue;
    if (count_ascii && ch >= 0 && ch < 128) {
      ++ascii_cnt;
      continue;
    }
    if (ch < 128) {
      if (ch < 91) {
        if (ch < 65) {
          counts[common] += 1;
        } else {
          counts[latin] += 1;
        }
      } else {
        if (ch < 97) {
          counts[common] += 1;
        } else {
          if (ch < 123) {
            counts[latin] += 1;
          } else {
            counts[common] += 1;
          }
        }
      }
    } else {
      if (ch < 65345) {
        if (ch < 4992) {
          if (ch < 2908) {
            if (ch < 2445) {
              if (ch < 1536) {
                if (ch < 902) {
                  if (ch < 746) {
                    if (ch < 215) {
                      if (ch < 186) {
                        if (ch < 170) {
                          counts[common] += 1;
                        } else {
                          if (ch < 171) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 187) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 192) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 248) {
                        if (ch < 216) {
                          counts[common] += 1;
                        } else {
                          if (ch < 247) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 736) {
                          if (ch < 697) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 741) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 888) {
                      if (ch < 880) {
                        if (ch < 748) {
                          counts[bopomofo] += 1;
                        } else {
                          if (ch < 768) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 884) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 885) {
                            counts[common] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 895) {
                        if (ch < 890) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 894) {
                            counts[greek] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 900) {
                          if (ch < 896) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 901) {
                            counts[greek] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 1159) {
                    if (ch < 910) {
                      if (ch < 907) {
                        if (ch < 903) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 904) {
                            counts[common] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 908) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 909) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 994) {
                        if (ch < 930) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 931) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 1024) {
                          if (ch < 1008) {
                            counts[coptic] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        } else {
                          if (ch < 1157) {
                            counts[cyrillic] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1424) {
                      if (ch < 1367) {
                        if (ch < 1328) {
                          counts[cyrillic] += 1;
                        } else {
                          if (ch < 1329) {
                            counts[unknown] += 1;
                          } else {
                            counts[armenian] += 1;
                          }
                        }
                      } else {
                        if (ch < 1419) {
                          if (ch < 1369) {
                            counts[unknown] += 1;
                          } else {
                            counts[armenian] += 1;
                          }
                        } else {
                          if (ch < 1421) {
                            counts[unknown] += 1;
                          } else {
                            counts[armenian] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1488) {
                        if (ch < 1425) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 1480) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 1519) {
                          if (ch < 1515) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 1525) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 2043) {
                  if (ch < 1648) {
                    if (ch < 1564) {
                      if (ch < 1548) {
                        if (ch < 1541) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1542) {
                            counts[common] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 1549) {
                          counts[common] += 1;
                        } else {
                          if (ch < 1563) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1600) {
                        if (ch < 1567) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1568) {
                            counts[common] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 1611) {
                          if (ch < 1601) {
                            counts[common] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        } else {
                          if (ch < 1622) {
                            counts[inherited] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1807) {
                      if (ch < 1758) {
                        if (ch < 1649) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 1757) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 1792) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1806) {
                            counts[syriac] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1872) {
                        if (ch < 1867) {
                          counts[syriac] += 1;
                        } else {
                          if (ch < 1869) {
                            counts[unknown] += 1;
                          } else {
                            counts[syriac] += 1;
                          }
                        }
                      } else {
                        if (ch < 1970) {
                          if (ch < 1920) {
                            counts[arabic] += 1;
                          } else {
                            counts[thaana] += 1;
                          }
                        } else {
                          if (ch < 1984) {
                            counts[unknown] += 1;
                          } else {
                            counts[nko] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2191) {
                    if (ch < 2112) {
                      if (ch < 2094) {
                        if (ch < 2045) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2048) {
                            counts[nko] += 1;
                          } else {
                            counts[samaritan] += 1;
                          }
                        }
                      } else {
                        if (ch < 2096) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2111) {
                            counts[samaritan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2143) {
                        if (ch < 2140) {
                          counts[mandaic] += 1;
                        } else {
                          if (ch < 2142) {
                            counts[unknown] += 1;
                          } else {
                            counts[mandaic] += 1;
                          }
                        }
                      } else {
                        if (ch < 2155) {
                          if (ch < 2144) {
                            counts[unknown] += 1;
                          } else {
                            counts[syriac] += 1;
                          }
                        } else {
                          if (ch < 2160) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2385) {
                      if (ch < 2199) {
                        if (ch < 2192) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2194) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2275) {
                          if (ch < 2274) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 2304) {
                            counts[arabic] += 1;
                          } else {
                            counts[devanagari] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2406) {
                        if (ch < 2389) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 2404) {
                            counts[devanagari] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 2436) {
                          if (ch < 2432) {
                            counts[devanagari] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        } else {
                          if (ch < 2437) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 2654) {
                if (ch < 2564) {
                  if (ch < 2503) {
                    if (ch < 2481) {
                      if (ch < 2451) {
                        if (ch < 2447) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2449) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2473) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2474) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2486) {
                        if (ch < 2482) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2483) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2492) {
                          if (ch < 2490) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 2501) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2524) {
                      if (ch < 2511) {
                        if (ch < 2505) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2507) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      } else {
                        if (ch < 2519) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2520) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2532) {
                        if (ch < 2526) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2527) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      } else {
                        if (ch < 2559) {
                          if (ch < 2534) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        } else {
                          if (ch < 2561) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2616) {
                    if (ch < 2601) {
                      if (ch < 2575) {
                        if (ch < 2565) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2571) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2577) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2579) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2610) {
                        if (ch < 2602) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2609) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2613) {
                          if (ch < 2612) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 2615) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2633) {
                      if (ch < 2621) {
                        if (ch < 2618) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2620) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      } else {
                        if (ch < 2627) {
                          if (ch < 2622) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        } else {
                          if (ch < 2631) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2641) {
                        if (ch < 2635) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2638) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2649) {
                          if (ch < 2642) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 2653) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 2788) {
                  if (ch < 2737) {
                    if (ch < 2693) {
                      if (ch < 2679) {
                        if (ch < 2655) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2662) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      } else {
                        if (ch < 2689) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2692) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2706) {
                        if (ch < 2702) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2703) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      } else {
                        if (ch < 2729) {
                          if (ch < 2707) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        } else {
                          if (ch < 2730) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2759) {
                      if (ch < 2741) {
                        if (ch < 2738) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2740) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2748) {
                          if (ch < 2746) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 2758) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2766) {
                        if (ch < 2762) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2763) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      } else {
                        if (ch < 2769) {
                          if (ch < 2768) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        } else {
                          if (ch < 2784) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2858) {
                    if (ch < 2820) {
                      if (ch < 2809) {
                        if (ch < 2790) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2802) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2816) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2817) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2831) {
                        if (ch < 2821) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2829) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2835) {
                          if (ch < 2833) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 2857) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2885) {
                      if (ch < 2868) {
                        if (ch < 2865) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2866) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      } else {
                        if (ch < 2874) {
                          if (ch < 2869) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        } else {
                          if (ch < 2876) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2891) {
                        if (ch < 2887) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2889) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2901) {
                          if (ch < 2894) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 2904) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 3479) {
              if (ch < 3159) {
                if (ch < 3006) {
                  if (ch < 2966) {
                    if (ch < 2946) {
                      if (ch < 2916) {
                        if (ch < 2910) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2911) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      } else {
                        if (ch < 2918) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2936) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2955) {
                        if (ch < 2948) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 2949) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      } else {
                        if (ch < 2961) {
                          if (ch < 2958) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        } else {
                          if (ch < 2962) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2976) {
                      if (ch < 2972) {
                        if (ch < 2969) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2971) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2973) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 2974) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2984) {
                        if (ch < 2979) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2981) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2990) {
                          if (ch < 2987) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 3002) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3085) {
                    if (ch < 3024) {
                      if (ch < 3017) {
                        if (ch < 3011) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 3014) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      } else {
                        if (ch < 3018) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3022) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3032) {
                        if (ch < 3025) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 3031) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      } else {
                        if (ch < 3067) {
                          if (ch < 3046) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        } else {
                          if (ch < 3072) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3132) {
                      if (ch < 3090) {
                        if (ch < 3086) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3089) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3114) {
                          if (ch < 3113) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 3130) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3145) {
                        if (ch < 3141) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3142) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      } else {
                        if (ch < 3150) {
                          if (ch < 3146) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        } else {
                          if (ch < 3157) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 3285) {
                  if (ch < 3217) {
                    if (ch < 3172) {
                      if (ch < 3165) {
                        if (ch < 3160) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3163) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3166) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3168) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3191) {
                        if (ch < 3174) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3184) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3213) {
                          if (ch < 3200) {
                            counts[telugu] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        } else {
                          if (ch < 3214) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3258) {
                      if (ch < 3242) {
                        if (ch < 3218) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3241) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3252) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3253) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3270) {
                        if (ch < 3260) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3269) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3274) {
                          if (ch < 3273) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 3278) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3345) {
                    if (ch < 3302) {
                      if (ch < 3295) {
                        if (ch < 3287) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3293) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      } else {
                        if (ch < 3296) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3300) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3316) {
                        if (ch < 3312) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3313) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      } else {
                        if (ch < 3341) {
                          if (ch < 3328) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        } else {
                          if (ch < 3342) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3412) {
                      if (ch < 3398) {
                        if (ch < 3346) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3397) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3402) {
                          if (ch < 3401) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 3408) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3456) {
                        if (ch < 3428) {
                          counts[malayalam] += 1;
                        } else {
                          if (ch < 3430) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        }
                      } else {
                        if (ch < 3460) {
                          if (ch < 3457) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        } else {
                          if (ch < 3461) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 3992) {
                if (ch < 3713) {
                  if (ch < 3542) {
                    if (ch < 3518) {
                      if (ch < 3507) {
                        if (ch < 3482) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3506) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3516) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3517) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3530) {
                        if (ch < 3520) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3527) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3535) {
                          if (ch < 3531) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 3541) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3570) {
                      if (ch < 3552) {
                        if (ch < 3543) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3544) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      } else {
                        if (ch < 3558) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3568) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3643) {
                        if (ch < 3573) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3585) {
                            counts[unknown] += 1;
                          } else {
                            counts[thai] += 1;
                          }
                        }
                      } else {
                        if (ch < 3648) {
                          if (ch < 3647) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 3676) {
                            counts[thai] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3781) {
                    if (ch < 3724) {
                      if (ch < 3717) {
                        if (ch < 3715) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3716) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      } else {
                        if (ch < 3718) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3723) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3750) {
                        if (ch < 3748) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3749) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      } else {
                        if (ch < 3774) {
                          if (ch < 3751) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        } else {
                          if (ch < 3776) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3804) {
                      if (ch < 3784) {
                        if (ch < 3782) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3783) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3792) {
                          if (ch < 3791) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 3802) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3912) {
                        if (ch < 3808) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3840) {
                            counts[unknown] += 1;
                          } else {
                            counts[tibetan] += 1;
                          }
                        }
                      } else {
                        if (ch < 3949) {
                          if (ch < 3913) {
                            counts[unknown] += 1;
                          } else {
                            counts[tibetan] += 1;
                          }
                        } else {
                          if (ch < 3953) {
                            counts[unknown] += 1;
                          } else {
                            counts[tibetan] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 4697) {
                  if (ch < 4296) {
                    if (ch < 4053) {
                      if (ch < 4030) {
                        if (ch < 3993) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4029) {
                            counts[tibetan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4045) {
                          counts[tibetan] += 1;
                        } else {
                          if (ch < 4046) {
                            counts[unknown] += 1;
                          } else {
                            counts[tibetan] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4096) {
                        if (ch < 4057) {
                          counts[common] += 1;
                        } else {
                          if (ch < 4059) {
                            counts[tibetan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4294) {
                          if (ch < 4256) {
                            counts[myanmar] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        } else {
                          if (ch < 4295) {
                            counts[unknown] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4608) {
                      if (ch < 4304) {
                        if (ch < 4301) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4302) {
                            counts[georgian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4348) {
                          if (ch < 4347) {
                            counts[georgian] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 4352) {
                            counts[georgian] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4686) {
                        if (ch < 4681) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4682) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 4695) {
                          if (ch < 4688) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        } else {
                          if (ch < 4696) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 4800) {
                    if (ch < 4750) {
                      if (ch < 4704) {
                        if (ch < 4698) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4702) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4745) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4746) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4786) {
                        if (ch < 4752) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4785) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4792) {
                          if (ch < 4790) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 4799) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4881) {
                      if (ch < 4806) {
                        if (ch < 4801) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4802) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 4823) {
                          if (ch < 4808) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        } else {
                          if (ch < 4824) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4888) {
                        if (ch < 4882) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4886) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4957) {
                          if (ch < 4955) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 4989) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        } else {
          if (ch < 11633) {
            if (ch < 7401) {
              if (ch < 6468) {
                if (ch < 6004) {
                  if (ch < 5888) {
                    if (ch < 5120) {
                      if (ch < 5110) {
                        if (ch < 5018) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 5024) {
                            counts[unknown] += 1;
                          } else {
                            counts[cherokee] += 1;
                          }
                        }
                      } else {
                        if (ch < 5112) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 5118) {
                            counts[cherokee] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 5792) {
                        if (ch < 5760) {
                          counts[canadian_aboriginal] += 1;
                        } else {
                          if (ch < 5789) {
                            counts[ogham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 5870) {
                          if (ch < 5867) {
                            counts[runic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 5881) {
                            counts[runic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 5952) {
                      if (ch < 5920) {
                        if (ch < 5910) {
                          counts[tagalog] += 1;
                        } else {
                          if (ch < 5919) {
                            counts[unknown] += 1;
                          } else {
                            counts[tagalog] += 1;
                          }
                        }
                      } else {
                        if (ch < 5941) {
                          counts[hanunoo] += 1;
                        } else {
                          if (ch < 5943) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 5997) {
                        if (ch < 5972) {
                          counts[buhid] += 1;
                        } else {
                          if (ch < 5984) {
                            counts[unknown] += 1;
                          } else {
                            counts[tagbanwa] += 1;
                          }
                        }
                      } else {
                        if (ch < 6001) {
                          if (ch < 5998) {
                            counts[unknown] += 1;
                          } else {
                            counts[tagbanwa] += 1;
                          }
                        } else {
                          if (ch < 6002) {
                            counts[unknown] += 1;
                          } else {
                            counts[tagbanwa] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 6176) {
                    if (ch < 6138) {
                      if (ch < 6112) {
                        if (ch < 6016) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6110) {
                            counts[khmer] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6122) {
                          counts[khmer] += 1;
                        } else {
                          if (ch < 6128) {
                            counts[unknown] += 1;
                          } else {
                            counts[khmer] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6148) {
                        if (ch < 6144) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6146) {
                            counts[mongolian] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 6150) {
                          if (ch < 6149) {
                            counts[mongolian] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 6170) {
                            counts[mongolian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6431) {
                      if (ch < 6315) {
                        if (ch < 6265) {
                          counts[mongolian] += 1;
                        } else {
                          if (ch < 6272) {
                            counts[unknown] += 1;
                          } else {
                            counts[mongolian] += 1;
                          }
                        }
                      } else {
                        if (ch < 6390) {
                          if (ch < 6320) {
                            counts[unknown] += 1;
                          } else {
                            counts[canadian_aboriginal] += 1;
                          }
                        } else {
                          if (ch < 6400) {
                            counts[unknown] += 1;
                          } else {
                            counts[limbu] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6448) {
                        if (ch < 6432) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6444) {
                            counts[limbu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6464) {
                          if (ch < 6460) {
                            counts[limbu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 6465) {
                            counts[limbu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 6832) {
                  if (ch < 6656) {
                    if (ch < 6572) {
                      if (ch < 6512) {
                        if (ch < 6480) {
                          counts[limbu] += 1;
                        } else {
                          if (ch < 6510) {
                            counts[tai_le] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6517) {
                          counts[tai_le] += 1;
                        } else {
                          if (ch < 6528) {
                            counts[unknown] += 1;
                          } else {
                            counts[new_tai_lue] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6608) {
                        if (ch < 6576) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6602) {
                            counts[new_tai_lue] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6622) {
                          if (ch < 6619) {
                            counts[new_tai_lue] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 6624) {
                            counts[new_tai_lue] += 1;
                          } else {
                            counts[khmer] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6781) {
                      if (ch < 6688) {
                        if (ch < 6684) {
                          counts[buginese] += 1;
                        } else {
                          if (ch < 6686) {
                            counts[unknown] += 1;
                          } else {
                            counts[buginese] += 1;
                          }
                        }
                      } else {
                        if (ch < 6751) {
                          counts[tai_tham] += 1;
                        } else {
                          if (ch < 6752) {
                            counts[unknown] += 1;
                          } else {
                            counts[tai_tham] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6800) {
                        if (ch < 6783) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6794) {
                            counts[tai_tham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6816) {
                          if (ch < 6810) {
                            counts[tai_tham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 6830) {
                            counts[tai_tham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 7245) {
                    if (ch < 7104) {
                      if (ch < 6989) {
                        if (ch < 6863) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 6912) {
                            counts[unknown] += 1;
                          } else {
                            counts[balinese] += 1;
                          }
                        }
                      } else {
                        if (ch < 6990) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 7040) {
                            counts[balinese] += 1;
                          } else {
                            counts[sundanese] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7168) {
                        if (ch < 7156) {
                          counts[batak] += 1;
                        } else {
                          if (ch < 7164) {
                            counts[unknown] += 1;
                          } else {
                            counts[batak] += 1;
                          }
                        }
                      } else {
                        if (ch < 7227) {
                          if (ch < 7224) {
                            counts[lepcha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 7242) {
                            counts[lepcha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7360) {
                      if (ch < 7307) {
                        if (ch < 7248) {
                          counts[lepcha] += 1;
                        } else {
                          if (ch < 7296) {
                            counts[ol_chiki] += 1;
                          } else {
                            counts[cyrillic] += 1;
                          }
                        }
                      } else {
                        if (ch < 7355) {
                          if (ch < 7312) {
                            counts[unknown] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        } else {
                          if (ch < 7357) {
                            counts[unknown] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7379) {
                        if (ch < 7368) {
                          counts[sundanese] += 1;
                        } else {
                          if (ch < 7376) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 7393) {
                          if (ch < 7380) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        } else {
                          if (ch < 7394) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 8192) {
                if (ch < 8006) {
                  if (ch < 7522) {
                    if (ch < 7418) {
                      if (ch < 7412) {
                        if (ch < 7405) {
                          counts[common] += 1;
                        } else {
                          if (ch < 7406) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 7413) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 7416) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7462) {
                        if (ch < 7419) {
                          counts[common] += 1;
                        } else {
                          if (ch < 7424) {
                            counts[unknown] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 7468) {
                          if (ch < 7467) {
                            counts[greek] += 1;
                          } else {
                            counts[cyrillic] += 1;
                          }
                        } else {
                          if (ch < 7517) {
                            counts[latin] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7616) {
                      if (ch < 7544) {
                        if (ch < 7526) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 7531) {
                            counts[greek] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 7545) {
                          counts[cyrillic] += 1;
                        } else {
                          if (ch < 7615) {
                            counts[latin] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7958) {
                        if (ch < 7680) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 7936) {
                            counts[latin] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 7966) {
                          if (ch < 7960) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        } else {
                          if (ch < 7968) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 8064) {
                    if (ch < 8026) {
                      if (ch < 8016) {
                        if (ch < 8008) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8014) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 8024) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8025) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8029) {
                        if (ch < 8027) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8028) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 8031) {
                          if (ch < 8030) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 8062) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8156) {
                      if (ch < 8133) {
                        if (ch < 8117) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8118) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 8148) {
                          if (ch < 8134) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        } else {
                          if (ch < 8150) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8178) {
                        if (ch < 8157) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8176) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 8182) {
                          if (ch < 8181) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 8191) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 8585) {
                  if (ch < 8352) {
                    if (ch < 8306) {
                      if (ch < 8293) {
                        if (ch < 8204) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8206) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 8294) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8305) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8320) {
                        if (ch < 8308) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8319) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 8336) {
                          if (ch < 8335) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 8349) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8490) {
                      if (ch < 8433) {
                        if (ch < 8385) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8400) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 8486) {
                          if (ch < 8448) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 8487) {
                            counts[greek] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8499) {
                        if (ch < 8492) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 8498) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 8527) {
                          if (ch < 8526) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        } else {
                          if (ch < 8544) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11264) {
                    if (ch < 9312) {
                      if (ch < 9258) {
                        if (ch < 8588) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8592) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 9280) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 9291) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11124) {
                        if (ch < 10240) {
                          counts[common] += 1;
                        } else {
                          if (ch < 10496) {
                            counts[braille] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 11158) {
                          if (ch < 11126) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 11159) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11559) {
                      if (ch < 11508) {
                        if (ch < 11360) {
                          counts[glagolitic] += 1;
                        } else {
                          if (ch < 11392) {
                            counts[latin] += 1;
                          } else {
                            counts[coptic] += 1;
                          }
                        }
                      } else {
                        if (ch < 11520) {
                          if (ch < 11513) {
                            counts[unknown] += 1;
                          } else {
                            counts[coptic] += 1;
                          }
                        } else {
                          if (ch < 11558) {
                            counts[georgian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11566) {
                        if (ch < 11560) {
                          counts[georgian] += 1;
                        } else {
                          if (ch < 11565) {
                            counts[unknown] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      } else {
                        if (ch < 11624) {
                          if (ch < 11568) {
                            counts[unknown] += 1;
                          } else {
                            counts[tifinagh] += 1;
                          }
                        } else {
                          if (ch < 11631) {
                            counts[unknown] += 1;
                          } else {
                            counts[tifinagh] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 43264) {
              if (ch < 12593) {
                if (ch < 12020) {
                  if (ch < 11719) {
                    if (ch < 11688) {
                      if (ch < 11671) {
                        if (ch < 11647) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11648) {
                            counts[tifinagh] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 11680) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11687) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11703) {
                        if (ch < 11695) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 11696) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 11711) {
                          if (ch < 11704) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        } else {
                          if (ch < 11712) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11743) {
                      if (ch < 11728) {
                        if (ch < 11720) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11727) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 11735) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 11736) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11870) {
                        if (ch < 11744) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11776) {
                            counts[cyrillic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 11930) {
                          if (ch < 11904) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        } else {
                          if (ch < 11931) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 12348) {
                    if (ch < 12295) {
                      if (ch < 12272) {
                        if (ch < 12032) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12246) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 12293) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12294) {
                            counts[han] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12330) {
                        if (ch < 12296) {
                          counts[han] += 1;
                        } else {
                          if (ch < 12321) {
                            counts[common] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      } else {
                        if (ch < 12336) {
                          if (ch < 12334) {
                            counts[inherited] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        } else {
                          if (ch < 12344) {
                            counts[common] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12448) {
                      if (ch < 12439) {
                        if (ch < 12352) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12353) {
                            counts[unknown] += 1;
                          } else {
                            counts[hiragana] += 1;
                          }
                        }
                      } else {
                        if (ch < 12443) {
                          if (ch < 12441) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        } else {
                          if (ch < 12445) {
                            counts[common] += 1;
                          } else {
                            counts[hiragana] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12541) {
                        if (ch < 12449) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12539) {
                            counts[katakana] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 12549) {
                          if (ch < 12544) {
                            counts[katakana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 12592) {
                            counts[bopomofo] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 42540) {
                  if (ch < 13008) {
                    if (ch < 12783) {
                      if (ch < 12704) {
                        if (ch < 12687) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 12688) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 12736) {
                          counts[bopomofo] += 1;
                        } else {
                          if (ch < 12774) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12831) {
                        if (ch < 12784) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12800) {
                            counts[katakana] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      } else {
                        if (ch < 12896) {
                          if (ch < 12832) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 12927) {
                            counts[hangul] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 19968) {
                      if (ch < 13144) {
                        if (ch < 13055) {
                          counts[katakana] += 1;
                        } else {
                          if (ch < 13056) {
                            counts[common] += 1;
                          } else {
                            counts[katakana] += 1;
                          }
                        }
                      } else {
                        if (ch < 13312) {
                          counts[common] += 1;
                        } else {
                          if (ch < 19904) {
                            counts[han] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 42128) {
                        if (ch < 40960) {
                          counts[han] += 1;
                        } else {
                          if (ch < 42125) {
                            counts[yi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 42192) {
                          if (ch < 42183) {
                            counts[yi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 42240) {
                            counts[lisu] += 1;
                          } else {
                            counts[vai] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 42965) {
                    if (ch < 42888) {
                      if (ch < 42744) {
                        if (ch < 42560) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 42656) {
                            counts[cyrillic] += 1;
                          } else {
                            counts[bamum] += 1;
                          }
                        }
                      } else {
                        if (ch < 42752) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 42786) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 42960) {
                        if (ch < 42891) {
                          counts[common] += 1;
                        } else {
                          if (ch < 42958) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 42963) {
                          if (ch < 42962) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 42964) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43072) {
                      if (ch < 43008) {
                        if (ch < 42973) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 42994) {
                            counts[unknown] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 43056) {
                          if (ch < 43053) {
                            counts[syloti_nagri] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 43066) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43206) {
                        if (ch < 43128) {
                          counts[phags_pa] += 1;
                        } else {
                          if (ch < 43136) {
                            counts[unknown] += 1;
                          } else {
                            counts[saurashtra] += 1;
                          }
                        }
                      } else {
                        if (ch < 43226) {
                          if (ch < 43214) {
                            counts[unknown] += 1;
                          } else {
                            counts[saurashtra] += 1;
                          }
                        } else {
                          if (ch < 43232) {
                            counts[unknown] += 1;
                          } else {
                            counts[devanagari] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 55216) {
                if (ch < 43739) {
                  if (ch < 43486) {
                    if (ch < 43360) {
                      if (ch < 43312) {
                        if (ch < 43310) {
                          counts[kayah_li] += 1;
                        } else {
                          if (ch < 43311) {
                            counts[common] += 1;
                          } else {
                            counts[kayah_li] += 1;
                          }
                        }
                      } else {
                        if (ch < 43348) {
                          counts[rejang] += 1;
                        } else {
                          if (ch < 43359) {
                            counts[unknown] += 1;
                          } else {
                            counts[rejang] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43470) {
                        if (ch < 43389) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 43392) {
                            counts[unknown] += 1;
                          } else {
                            counts[javanese] += 1;
                          }
                        }
                      } else {
                        if (ch < 43472) {
                          if (ch < 43471) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 43482) {
                            counts[javanese] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43598) {
                      if (ch < 43520) {
                        if (ch < 43488) {
                          counts[javanese] += 1;
                        } else {
                          if (ch < 43519) {
                            counts[myanmar] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 43575) {
                          counts[cham] += 1;
                        } else {
                          if (ch < 43584) {
                            counts[unknown] += 1;
                          } else {
                            counts[cham] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43612) {
                        if (ch < 43600) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43610) {
                            counts[cham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 43648) {
                          if (ch < 43616) {
                            counts[cham] += 1;
                          } else {
                            counts[myanmar] += 1;
                          }
                        } else {
                          if (ch < 43715) {
                            counts[tai_viet] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 43824) {
                    if (ch < 43791) {
                      if (ch < 43777) {
                        if (ch < 43744) {
                          counts[tai_viet] += 1;
                        } else {
                          if (ch < 43767) {
                            counts[meetei_mayek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 43783) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 43785) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43808) {
                        if (ch < 43793) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43799) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 43816) {
                          if (ch < 43815) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 43823) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43888) {
                      if (ch < 43877) {
                        if (ch < 43867) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 43868) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 43882) {
                          if (ch < 43878) {
                            counts[greek] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        } else {
                          if (ch < 43884) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 44016) {
                        if (ch < 43968) {
                          counts[cherokee] += 1;
                        } else {
                          if (ch < 44014) {
                            counts[meetei_mayek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 44032) {
                          if (ch < 44026) {
                            counts[meetei_mayek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 55204) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 64832) {
                  if (ch < 64311) {
                    if (ch < 64112) {
                      if (ch < 55292) {
                        if (ch < 55239) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 55243) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      } else {
                        if (ch < 63744) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64110) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 64263) {
                        if (ch < 64218) {
                          counts[han] += 1;
                        } else {
                          if (ch < 64256) {
                            counts[unknown] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 64280) {
                          if (ch < 64275) {
                            counts[unknown] += 1;
                          } else {
                            counts[armenian] += 1;
                          }
                        } else {
                          if (ch < 64285) {
                            counts[unknown] += 1;
                          } else {
                            counts[hebrew] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 64323) {
                      if (ch < 64318) {
                        if (ch < 64312) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64317) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 64320) {
                          if (ch < 64319) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 64322) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 64336) {
                        if (ch < 64325) {
                          counts[hebrew] += 1;
                        } else {
                          if (ch < 64326) {
                            counts[unknown] += 1;
                          } else {
                            counts[hebrew] += 1;
                          }
                        }
                      } else {
                        if (ch < 64467) {
                          if (ch < 64451) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 64830) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 65107) {
                    if (ch < 65008) {
                      if (ch < 64968) {
                        if (ch < 64912) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 64914) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 64975) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64976) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65050) {
                        if (ch < 65024) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 65040) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65070) {
                          if (ch < 65056) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        } else {
                          if (ch < 65072) {
                            counts[cyrillic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65142) {
                      if (ch < 65128) {
                        if (ch < 65108) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65127) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 65136) {
                          if (ch < 65132) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 65141) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65280) {
                        if (ch < 65277) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 65279) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65313) {
                          if (ch < 65281) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 65339) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      } else {
        if (ch < 73103) {
          if (ch < 69294) {
            if (ch < 67392) {
              if (ch < 66257) {
                if (ch < 65576) {
                  if (ch < 65496) {
                    if (ch < 65440) {
                      if (ch < 65392) {
                        if (ch < 65371) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 65382) {
                            counts[common] += 1;
                          } else {
                            counts[katakana] += 1;
                          }
                        }
                      } else {
                        if (ch < 65393) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65438) {
                            counts[katakana] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65480) {
                        if (ch < 65471) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 65474) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      } else {
                        if (ch < 65488) {
                          if (ch < 65482) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        } else {
                          if (ch < 65490) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65519) {
                      if (ch < 65504) {
                        if (ch < 65498) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65501) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 65511) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65512) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65536) {
                        if (ch < 65529) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65534) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 65549) {
                          if (ch < 65548) {
                            counts[linear_b] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 65575) {
                            counts[linear_b] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 65844) {
                    if (ch < 65616) {
                      if (ch < 65598) {
                        if (ch < 65595) {
                          counts[linear_b] += 1;
                        } else {
                          if (ch < 65596) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_b] += 1;
                          }
                        }
                      } else {
                        if (ch < 65599) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65614) {
                            counts[linear_b] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65787) {
                        if (ch < 65630) {
                          counts[linear_b] += 1;
                        } else {
                          if (ch < 65664) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_b] += 1;
                          }
                        }
                      } else {
                        if (ch < 65795) {
                          if (ch < 65792) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 65799) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65953) {
                      if (ch < 65935) {
                        if (ch < 65847) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65856) {
                            counts[common] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 65949) {
                          if (ch < 65936) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 65952) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66046) {
                        if (ch < 66000) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66045) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 66205) {
                          if (ch < 66176) {
                            counts[unknown] += 1;
                          } else {
                            counts[lycian] += 1;
                          }
                        } else {
                          if (ch < 66208) {
                            counts[unknown] += 1;
                          } else {
                            counts[carian] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 66776) {
                  if (ch < 66463) {
                    if (ch < 66349) {
                      if (ch < 66300) {
                        if (ch < 66272) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66273) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 66304) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66340) {
                            counts[old_italic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66384) {
                        if (ch < 66352) {
                          counts[old_italic] += 1;
                        } else {
                          if (ch < 66379) {
                            counts[gothic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 66432) {
                          if (ch < 66427) {
                            counts[old_permic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 66462) {
                            counts[ugaritic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 66640) {
                      if (ch < 66504) {
                        if (ch < 66464) {
                          counts[ugaritic] += 1;
                        } else {
                          if (ch < 66500) {
                            counts[old_persian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 66518) {
                          counts[old_persian] += 1;
                        } else {
                          if (ch < 66560) {
                            counts[unknown] += 1;
                          } else {
                            counts[deseret] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66720) {
                        if (ch < 66688) {
                          counts[shavian] += 1;
                        } else {
                          if (ch < 66718) {
                            counts[osmanya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 66736) {
                          if (ch < 66730) {
                            counts[osmanya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 66772) {
                            counts[osage] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 66964) {
                    if (ch < 66927) {
                      if (ch < 66856) {
                        if (ch < 66812) {
                          counts[osage] += 1;
                        } else {
                          if (ch < 66816) {
                            counts[unknown] += 1;
                          } else {
                            counts[elbasan] += 1;
                          }
                        }
                      } else {
                        if (ch < 66864) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66916) {
                            counts[caucasian_albanian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66940) {
                        if (ch < 66928) {
                          counts[caucasian_albanian] += 1;
                        } else {
                          if (ch < 66939) {
                            counts[vithkuqi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 66956) {
                          if (ch < 66955) {
                            counts[vithkuqi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 66963) {
                            counts[vithkuqi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 67002) {
                      if (ch < 66978) {
                        if (ch < 66966) {
                          counts[vithkuqi] += 1;
                        } else {
                          if (ch < 66967) {
                            counts[unknown] += 1;
                          } else {
                            counts[vithkuqi] += 1;
                          }
                        }
                      } else {
                        if (ch < 66994) {
                          if (ch < 66979) {
                            counts[unknown] += 1;
                          } else {
                            counts[vithkuqi] += 1;
                          }
                        } else {
                          if (ch < 66995) {
                            counts[unknown] += 1;
                          } else {
                            counts[vithkuqi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67008) {
                        if (ch < 67003) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67005) {
                            counts[vithkuqi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 67072) {
                          if (ch < 67060) {
                            counts[todhri] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 67383) {
                            counts[linear_a] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 68117) {
                if (ch < 67743) {
                  if (ch < 67593) {
                    if (ch < 67463) {
                      if (ch < 67432) {
                        if (ch < 67414) {
                          counts[linear_a] += 1;
                        } else {
                          if (ch < 67424) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_a] += 1;
                          }
                        }
                      } else {
                        if (ch < 67456) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67462) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67515) {
                        if (ch < 67505) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 67506) {
                            counts[unknown] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 67590) {
                          if (ch < 67584) {
                            counts[unknown] += 1;
                          } else {
                            counts[cypriot] += 1;
                          }
                        } else {
                          if (ch < 67592) {
                            counts[unknown] += 1;
                          } else {
                            counts[cypriot] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 67645) {
                      if (ch < 67639) {
                        if (ch < 67594) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67638) {
                            counts[cypriot] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 67641) {
                          counts[cypriot] += 1;
                        } else {
                          if (ch < 67644) {
                            counts[unknown] += 1;
                          } else {
                            counts[cypriot] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67670) {
                        if (ch < 67647) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67648) {
                            counts[cypriot] += 1;
                          } else {
                            counts[imperial_aramaic] += 1;
                          }
                        }
                      } else {
                        if (ch < 67680) {
                          if (ch < 67671) {
                            counts[unknown] += 1;
                          } else {
                            counts[imperial_aramaic] += 1;
                          }
                        } else {
                          if (ch < 67712) {
                            counts[palmyrene] += 1;
                          } else {
                            counts[nabataean] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 67903) {
                    if (ch < 67830) {
                      if (ch < 67808) {
                        if (ch < 67751) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67760) {
                            counts[nabataean] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 67827) {
                          counts[hatran] += 1;
                        } else {
                          if (ch < 67828) {
                            counts[unknown] += 1;
                          } else {
                            counts[hatran] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67868) {
                        if (ch < 67835) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67840) {
                            counts[hatran] += 1;
                          } else {
                            counts[phoenician] += 1;
                          }
                        }
                      } else {
                        if (ch < 67872) {
                          if (ch < 67871) {
                            counts[unknown] += 1;
                          } else {
                            counts[phoenician] += 1;
                          }
                        } else {
                          if (ch < 67898) {
                            counts[lydian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 68050) {
                      if (ch < 68000) {
                        if (ch < 67904) {
                          counts[lydian] += 1;
                        } else {
                          if (ch < 67968) {
                            counts[unknown] += 1;
                          } else {
                            counts[meroitic_hieroglyphs] += 1;
                          }
                        }
                      } else {
                        if (ch < 68028) {
                          if (ch < 68024) {
                            counts[meroitic_cursive] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 68048) {
                            counts[meroitic_cursive] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68101) {
                        if (ch < 68096) {
                          counts[meroitic_cursive] += 1;
                        } else {
                          if (ch < 68100) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68108) {
                          if (ch < 68103) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 68116) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 68498) {
                  if (ch < 68288) {
                    if (ch < 68159) {
                      if (ch < 68150) {
                        if (ch < 68120) {
                          counts[kharoshthi] += 1;
                        } else {
                          if (ch < 68121) {
                            counts[unknown] += 1;
                          } else {
                            counts[kharoshthi] += 1;
                          }
                        }
                      } else {
                        if (ch < 68152) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68155) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68185) {
                        if (ch < 68169) {
                          counts[kharoshthi] += 1;
                        } else {
                          if (ch < 68176) {
                            counts[unknown] += 1;
                          } else {
                            counts[kharoshthi] += 1;
                          }
                        }
                      } else {
                        if (ch < 68224) {
                          if (ch < 68192) {
                            counts[unknown] += 1;
                          } else {
                            counts[old_south_arabian] += 1;
                          }
                        } else {
                          if (ch < 68256) {
                            counts[old_north_arabian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 68416) {
                      if (ch < 68343) {
                        if (ch < 68327) {
                          counts[manichaean] += 1;
                        } else {
                          if (ch < 68331) {
                            counts[unknown] += 1;
                          } else {
                            counts[manichaean] += 1;
                          }
                        }
                      } else {
                        if (ch < 68406) {
                          if (ch < 68352) {
                            counts[unknown] += 1;
                          } else {
                            counts[avestan] += 1;
                          }
                        } else {
                          if (ch < 68409) {
                            counts[unknown] += 1;
                          } else {
                            counts[avestan] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68448) {
                        if (ch < 68438) {
                          counts[inscriptional_parthian] += 1;
                        } else {
                          if (ch < 68440) {
                            counts[unknown] += 1;
                          } else {
                            counts[inscriptional_parthian] += 1;
                          }
                        }
                      } else {
                        if (ch < 68472) {
                          if (ch < 68467) {
                            counts[inscriptional_pahlavi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 68480) {
                            counts[inscriptional_pahlavi] += 1;
                          } else {
                            counts[psalter_pahlavi] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 68904) {
                    if (ch < 68681) {
                      if (ch < 68521) {
                        if (ch < 68505) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68509) {
                            counts[psalter_pahlavi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68528) {
                          counts[psalter_pahlavi] += 1;
                        } else {
                          if (ch < 68608) {
                            counts[unknown] += 1;
                          } else {
                            counts[old_turkic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68800) {
                        if (ch < 68736) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68787) {
                            counts[old_hungarian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68858) {
                          if (ch < 68851) {
                            counts[old_hungarian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 68864) {
                            counts[old_hungarian] += 1;
                          } else {
                            counts[hanifi_rohingya] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 69006) {
                      if (ch < 68928) {
                        if (ch < 68912) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68922) {
                            counts[hanifi_rohingya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68969) {
                          if (ch < 68966) {
                            counts[garay] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 68998) {
                            counts[garay] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 69247) {
                        if (ch < 69008) {
                          counts[garay] += 1;
                        } else {
                          if (ch < 69216) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 69290) {
                          if (ch < 69248) {
                            counts[unknown] += 1;
                          } else {
                            counts[yezidi] += 1;
                          }
                        } else {
                          if (ch < 69291) {
                            counts[unknown] += 1;
                          } else {
                            counts[yezidi] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 70615) {
              if (ch < 70320) {
                if (ch < 69865) {
                  if (ch < 69580) {
                    if (ch < 69376) {
                      if (ch < 69314) {
                        if (ch < 69296) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 69298) {
                            counts[yezidi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 69317) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 69372) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 69466) {
                        if (ch < 69416) {
                          counts[old_sogdian] += 1;
                        } else {
                          if (ch < 69424) {
                            counts[unknown] += 1;
                          } else {
                            counts[sogdian] += 1;
                          }
                        }
                      } else {
                        if (ch < 69514) {
                          if (ch < 69488) {
                            counts[unknown] += 1;
                          } else {
                            counts[old_uyghur] += 1;
                          }
                        } else {
                          if (ch < 69552) {
                            counts[unknown] += 1;
                          } else {
                            counts[chorasmian] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 69750) {
                      if (ch < 69632) {
                        if (ch < 69600) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 69623) {
                            counts[elymaic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 69710) {
                          counts[brahmi] += 1;
                        } else {
                          if (ch < 69714) {
                            counts[unknown] += 1;
                          } else {
                            counts[brahmi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 69827) {
                        if (ch < 69759) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 69760) {
                            counts[brahmi] += 1;
                          } else {
                            counts[kaithi] += 1;
                          }
                        }
                      } else {
                        if (ch < 69838) {
                          if (ch < 69837) {
                            counts[unknown] += 1;
                          } else {
                            counts[kaithi] += 1;
                          }
                        } else {
                          if (ch < 69840) {
                            counts[unknown] += 1;
                          } else {
                            counts[sora_sompeng] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 70144) {
                    if (ch < 69960) {
                      if (ch < 69888) {
                        if (ch < 69872) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 69882) {
                            counts[sora_sompeng] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 69941) {
                          counts[chakma] += 1;
                        } else {
                          if (ch < 69942) {
                            counts[unknown] += 1;
                          } else {
                            counts[chakma] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70016) {
                        if (ch < 69968) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70007) {
                            counts[mahajani] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 70113) {
                          if (ch < 70112) {
                            counts[sharada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 70133) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70281) {
                      if (ch < 70210) {
                        if (ch < 70162) {
                          counts[khojki] += 1;
                        } else {
                          if (ch < 70163) {
                            counts[unknown] += 1;
                          } else {
                            counts[khojki] += 1;
                          }
                        }
                      } else {
                        if (ch < 70279) {
                          if (ch < 70272) {
                            counts[unknown] += 1;
                          } else {
                            counts[multani] += 1;
                          }
                        } else {
                          if (ch < 70280) {
                            counts[unknown] += 1;
                          } else {
                            counts[multani] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70287) {
                        if (ch < 70282) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70286) {
                            counts[multani] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 70303) {
                          if (ch < 70302) {
                            counts[multani] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 70314) {
                            counts[multani] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 70481) {
                  if (ch < 70449) {
                    if (ch < 70405) {
                      if (ch < 70394) {
                        if (ch < 70379) {
                          counts[khudawadi] += 1;
                        } else {
                          if (ch < 70384) {
                            counts[unknown] += 1;
                          } else {
                            counts[khudawadi] += 1;
                          }
                        }
                      } else {
                        if (ch < 70400) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70404) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70417) {
                        if (ch < 70413) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70415) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      } else {
                        if (ch < 70441) {
                          if (ch < 70419) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        } else {
                          if (ch < 70442) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70460) {
                      if (ch < 70453) {
                        if (ch < 70450) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70452) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 70458) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70459) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70473) {
                        if (ch < 70469) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70471) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      } else {
                        if (ch < 70478) {
                          if (ch < 70475) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        } else {
                          if (ch < 70480) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 70542) {
                    if (ch < 70509) {
                      if (ch < 70493) {
                        if (ch < 70487) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70488) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 70500) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70502) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70528) {
                        if (ch < 70512) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70517) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 70539) {
                          if (ch < 70538) {
                            counts[tulu_tigalari] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 70540) {
                            counts[tulu_tigalari] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70595) {
                      if (ch < 70582) {
                        if (ch < 70543) {
                          counts[tulu_tigalari] += 1;
                        } else {
                          if (ch < 70544) {
                            counts[unknown] += 1;
                          } else {
                            counts[tulu_tigalari] += 1;
                          }
                        }
                      } else {
                        if (ch < 70593) {
                          if (ch < 70583) {
                            counts[unknown] += 1;
                          } else {
                            counts[tulu_tigalari] += 1;
                          }
                        } else {
                          if (ch < 70594) {
                            counts[unknown] += 1;
                          } else {
                            counts[tulu_tigalari] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70599) {
                        if (ch < 70597) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70598) {
                            counts[tulu_tigalari] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 70604) {
                          if (ch < 70603) {
                            counts[tulu_tigalari] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 70614) {
                            counts[tulu_tigalari] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 72016) {
                if (ch < 71376) {
                  if (ch < 71094) {
                    if (ch < 70749) {
                      if (ch < 70627) {
                        if (ch < 70617) {
                          counts[tulu_tigalari] += 1;
                        } else {
                          if (ch < 70625) {
                            counts[unknown] += 1;
                          } else {
                            counts[tulu_tigalari] += 1;
                          }
                        }
                      } else {
                        if (ch < 70656) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70748) {
                            counts[newa] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70856) {
                        if (ch < 70754) {
                          counts[newa] += 1;
                        } else {
                          if (ch < 70784) {
                            counts[unknown] += 1;
                          } else {
                            counts[tirhuta] += 1;
                          }
                        }
                      } else {
                        if (ch < 70874) {
                          if (ch < 70864) {
                            counts[unknown] += 1;
                          } else {
                            counts[tirhuta] += 1;
                          }
                        } else {
                          if (ch < 71040) {
                            counts[unknown] += 1;
                          } else {
                            counts[siddham] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 71258) {
                      if (ch < 71168) {
                        if (ch < 71096) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71134) {
                            counts[siddham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 71237) {
                          counts[modi] += 1;
                        } else {
                          if (ch < 71248) {
                            counts[unknown] += 1;
                          } else {
                            counts[modi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 71296) {
                        if (ch < 71264) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71277) {
                            counts[mongolian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 71360) {
                          if (ch < 71354) {
                            counts[takri] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 71370) {
                            counts[takri] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 71936) {
                    if (ch < 71472) {
                      if (ch < 71451) {
                        if (ch < 71396) {
                          counts[myanmar] += 1;
                        } else {
                          if (ch < 71424) {
                            counts[unknown] += 1;
                          } else {
                            counts[ahom] += 1;
                          }
                        }
                      } else {
                        if (ch < 71453) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71468) {
                            counts[ahom] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 71740) {
                        if (ch < 71495) {
                          counts[ahom] += 1;
                        } else {
                          if (ch < 71680) {
                            counts[unknown] += 1;
                          } else {
                            counts[dogra] += 1;
                          }
                        }
                      } else {
                        if (ch < 71923) {
                          if (ch < 71840) {
                            counts[unknown] += 1;
                          } else {
                            counts[warang_citi] += 1;
                          }
                        } else {
                          if (ch < 71935) {
                            counts[unknown] += 1;
                          } else {
                            counts[warang_citi] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 71959) {
                      if (ch < 71946) {
                        if (ch < 71943) {
                          counts[dives_akuru] += 1;
                        } else {
                          if (ch < 71945) {
                            counts[unknown] += 1;
                          } else {
                            counts[dives_akuru] += 1;
                          }
                        }
                      } else {
                        if (ch < 71956) {
                          if (ch < 71948) {
                            counts[unknown] += 1;
                          } else {
                            counts[dives_akuru] += 1;
                          }
                        } else {
                          if (ch < 71957) {
                            counts[unknown] += 1;
                          } else {
                            counts[dives_akuru] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 71991) {
                        if (ch < 71960) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71990) {
                            counts[dives_akuru] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 71995) {
                          if (ch < 71993) {
                            counts[dives_akuru] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 72007) {
                            counts[dives_akuru] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 72784) {
                  if (ch < 72384) {
                    if (ch < 72154) {
                      if (ch < 72104) {
                        if (ch < 72026) {
                          counts[dives_akuru] += 1;
                        } else {
                          if (ch < 72096) {
                            counts[unknown] += 1;
                          } else {
                            counts[nandinagari] += 1;
                          }
                        }
                      } else {
                        if (ch < 72106) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 72152) {
                            counts[nandinagari] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 72264) {
                        if (ch < 72165) {
                          counts[nandinagari] += 1;
                        } else {
                          if (ch < 72192) {
                            counts[unknown] += 1;
                          } else {
                            counts[zanabazar_square] += 1;
                          }
                        }
                      } else {
                        if (ch < 72355) {
                          if (ch < 72272) {
                            counts[unknown] += 1;
                          } else {
                            counts[soyombo] += 1;
                          }
                        } else {
                          if (ch < 72368) {
                            counts[unknown] += 1;
                          } else {
                            counts[canadian_aboriginal] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 72698) {
                      if (ch < 72458) {
                        if (ch < 72441) {
                          counts[pau_cin_hau] += 1;
                        } else {
                          if (ch < 72448) {
                            counts[unknown] += 1;
                          } else {
                            counts[devanagari] += 1;
                          }
                        }
                      } else {
                        if (ch < 72674) {
                          if (ch < 72640) {
                            counts[unknown] += 1;
                          } else {
                            counts[sunuwar] += 1;
                          }
                        } else {
                          if (ch < 72688) {
                            counts[unknown] += 1;
                          } else {
                            counts[sunuwar] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 72714) {
                        if (ch < 72704) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 72713) {
                            counts[bhaiksuki] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 72760) {
                          if (ch < 72759) {
                            counts[bhaiksuki] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 72774) {
                            counts[bhaiksuki] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 73015) {
                    if (ch < 72873) {
                      if (ch < 72848) {
                        if (ch < 72813) {
                          counts[bhaiksuki] += 1;
                        } else {
                          if (ch < 72816) {
                            counts[unknown] += 1;
                          } else {
                            counts[marchen] += 1;
                          }
                        }
                      } else {
                        if (ch < 72850) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 72872) {
                            counts[marchen] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 72967) {
                        if (ch < 72887) {
                          counts[marchen] += 1;
                        } else {
                          if (ch < 72960) {
                            counts[unknown] += 1;
                          } else {
                            counts[masaram_gondi] += 1;
                          }
                        }
                      } else {
                        if (ch < 72970) {
                          if (ch < 72968) {
                            counts[unknown] += 1;
                          } else {
                            counts[masaram_gondi] += 1;
                          }
                        } else {
                          if (ch < 72971) {
                            counts[unknown] += 1;
                          } else {
                            counts[masaram_gondi] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 73040) {
                      if (ch < 73020) {
                        if (ch < 73018) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 73019) {
                            counts[masaram_gondi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 73023) {
                          if (ch < 73022) {
                            counts[masaram_gondi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 73032) {
                            counts[masaram_gondi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 73062) {
                        if (ch < 73050) {
                          counts[masaram_gondi] += 1;
                        } else {
                          if (ch < 73056) {
                            counts[unknown] += 1;
                          } else {
                            counts[gunjala_gondi] += 1;
                          }
                        }
                      } else {
                        if (ch < 73065) {
                          if (ch < 73063) {
                            counts[unknown] += 1;
                          } else {
                            counts[gunjala_gondi] += 1;
                          }
                        } else {
                          if (ch < 73066) {
                            counts[unknown] += 1;
                          } else {
                            counts[gunjala_gondi] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        } else {
          if (ch < 122923) {
            if (ch < 110960) {
              if (ch < 92928) {
                if (ch < 74880) {
                  if (ch < 73534) {
                    if (ch < 73130) {
                      if (ch < 73107) {
                        if (ch < 73104) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 73106) {
                            counts[gunjala_gondi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 73113) {
                          counts[gunjala_gondi] += 1;
                        } else {
                          if (ch < 73120) {
                            counts[unknown] += 1;
                          } else {
                            counts[gunjala_gondi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 73472) {
                        if (ch < 73440) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 73465) {
                            counts[makasar] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 73490) {
                          if (ch < 73489) {
                            counts[kawi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 73531) {
                            counts[kawi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 73727) {
                      if (ch < 73649) {
                        if (ch < 73563) {
                          counts[kawi] += 1;
                        } else {
                          if (ch < 73648) {
                            counts[unknown] += 1;
                          } else {
                            counts[lisu] += 1;
                          }
                        }
                      } else {
                        if (ch < 73664) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 73714) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 74752) {
                        if (ch < 73728) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 74650) {
                            counts[cuneiform] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 74864) {
                          if (ch < 74863) {
                            counts[cuneiform] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 74869) {
                            counts[cuneiform] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 92729) {
                    if (ch < 78944) {
                      if (ch < 77811) {
                        if (ch < 75076) {
                          counts[cuneiform] += 1;
                        } else {
                          if (ch < 77712) {
                            counts[unknown] += 1;
                          } else {
                            counts[cypro_minoan] += 1;
                          }
                        }
                      } else {
                        if (ch < 77824) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 78934) {
                            counts[egyptian_hieroglyphs] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 83527) {
                        if (ch < 82939) {
                          counts[egyptian_hieroglyphs] += 1;
                        } else {
                          if (ch < 82944) {
                            counts[unknown] += 1;
                          } else {
                            counts[anatolian_hieroglyphs] += 1;
                          }
                        }
                      } else {
                        if (ch < 90426) {
                          if (ch < 90368) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurung_khema] += 1;
                          }
                        } else {
                          if (ch < 92160) {
                            counts[unknown] += 1;
                          } else {
                            counts[bamum] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 92863) {
                      if (ch < 92768) {
                        if (ch < 92736) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 92767) {
                            counts[mro] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 92782) {
                          if (ch < 92778) {
                            counts[mro] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 92784) {
                            counts[mro] += 1;
                          } else {
                            counts[tangsa] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 92880) {
                        if (ch < 92864) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 92874) {
                            counts[tangsa] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 92912) {
                          if (ch < 92910) {
                            counts[bassa_vah] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 92918) {
                            counts[bassa_vah] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 94194) {
                  if (ch < 93851) {
                    if (ch < 93027) {
                      if (ch < 93018) {
                        if (ch < 92998) {
                          counts[pahawh_hmong] += 1;
                        } else {
                          if (ch < 93008) {
                            counts[unknown] += 1;
                          } else {
                            counts[pahawh_hmong] += 1;
                          }
                        }
                      } else {
                        if (ch < 93019) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 93026) {
                            counts[pahawh_hmong] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 93072) {
                        if (ch < 93048) {
                          counts[pahawh_hmong] += 1;
                        } else {
                          if (ch < 93053) {
                            counts[unknown] += 1;
                          } else {
                            counts[pahawh_hmong] += 1;
                          }
                        }
                      } else {
                        if (ch < 93562) {
                          if (ch < 93504) {
                            counts[unknown] += 1;
                          } else {
                            counts[kirat_rai] += 1;
                          }
                        } else {
                          if (ch < 93760) {
                            counts[unknown] += 1;
                          } else {
                            counts[medefaidrin] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 94112) {
                      if (ch < 94031) {
                        if (ch < 93952) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 94027) {
                            counts[miao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 94088) {
                          counts[miao] += 1;
                        } else {
                          if (ch < 94095) {
                            counts[unknown] += 1;
                          } else {
                            counts[miao] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 94178) {
                        if (ch < 94176) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 94177) {
                            counts[tangut] += 1;
                          } else {
                            counts[nushu] += 1;
                          }
                        }
                      } else {
                        if (ch < 94181) {
                          if (ch < 94180) {
                            counts[han] += 1;
                          } else {
                            counts[khitan_small_script] += 1;
                          }
                        } else {
                          if (ch < 94192) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 110589) {
                    if (ch < 101631) {
                      if (ch < 100352) {
                        if (ch < 94208) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 100344) {
                            counts[tangut] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 101120) {
                          counts[tangut] += 1;
                        } else {
                          if (ch < 101590) {
                            counts[khitan_small_script] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 110576) {
                        if (ch < 101632) {
                          counts[khitan_small_script] += 1;
                        } else {
                          if (ch < 101641) {
                            counts[tangut] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 110581) {
                          if (ch < 110580) {
                            counts[katakana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 110588) {
                            counts[katakana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 110899) {
                      if (ch < 110593) {
                        if (ch < 110591) {
                          counts[katakana] += 1;
                        } else {
                          if (ch < 110592) {
                            counts[unknown] += 1;
                          } else {
                            counts[katakana] += 1;
                          }
                        }
                      } else {
                        if (ch < 110883) {
                          if (ch < 110880) {
                            counts[hiragana] += 1;
                          } else {
                            counts[katakana] += 1;
                          }
                        } else {
                          if (ch < 110898) {
                            counts[unknown] += 1;
                          } else {
                            counts[hiragana] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 110933) {
                        if (ch < 110928) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 110931) {
                            counts[hiragana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 110948) {
                          if (ch < 110934) {
                            counts[katakana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 110952) {
                            counts[katakana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 119970) {
                if (ch < 119079) {
                  if (ch < 117760) {
                    if (ch < 113792) {
                      if (ch < 113771) {
                        if (ch < 111356) {
                          counts[nushu] += 1;
                        } else {
                          if (ch < 113664) {
                            counts[unknown] += 1;
                          } else {
                            counts[duployan] += 1;
                          }
                        }
                      } else {
                        if (ch < 113776) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 113789) {
                            counts[duployan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 113818) {
                        if (ch < 113801) {
                          counts[duployan] += 1;
                        } else {
                          if (ch < 113808) {
                            counts[unknown] += 1;
                          } else {
                            counts[duployan] += 1;
                          }
                        }
                      } else {
                        if (ch < 113824) {
                          if (ch < 113820) {
                            counts[unknown] += 1;
                          } else {
                            counts[duployan] += 1;
                          }
                        } else {
                          if (ch < 113828) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 118576) {
                      if (ch < 118452) {
                        if (ch < 118010) {
                          counts[common] += 1;
                        } else {
                          if (ch < 118016) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 118528) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 118574) {
                            counts[inherited] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 118724) {
                        if (ch < 118599) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 118608) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119030) {
                          if (ch < 118784) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 119040) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 119488) {
                    if (ch < 119173) {
                      if (ch < 119146) {
                        if (ch < 119081) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119143) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 119163) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119171) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119214) {
                        if (ch < 119180) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 119210) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 119296) {
                          if (ch < 119275) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 119366) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 119673) {
                      if (ch < 119540) {
                        if (ch < 119508) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119520) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119639) {
                          if (ch < 119552) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 119648) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119894) {
                        if (ch < 119808) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119893) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 119966) {
                          if (ch < 119965) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 119968) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 120135) {
                  if (ch < 120070) {
                    if (ch < 119982) {
                      if (ch < 119975) {
                        if (ch < 119971) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119973) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119977) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119981) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119996) {
                        if (ch < 119994) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119995) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 120004) {
                          if (ch < 119997) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 120005) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 120094) {
                      if (ch < 120077) {
                        if (ch < 120071) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120075) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 120086) {
                          if (ch < 120085) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 120093) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 120127) {
                        if (ch < 120122) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120123) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 120133) {
                          if (ch < 120128) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 120134) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 121520) {
                    if (ch < 120780) {
                      if (ch < 120146) {
                        if (ch < 120138) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120145) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 120486) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120488) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 121484) {
                        if (ch < 120782) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120832) {
                            counts[common] += 1;
                          } else {
                            counts[signwriting] += 1;
                          }
                        }
                      } else {
                        if (ch < 121504) {
                          if (ch < 121499) {
                            counts[unknown] += 1;
                          } else {
                            counts[signwriting] += 1;
                          }
                        } else {
                          if (ch < 121505) {
                            counts[unknown] += 1;
                          } else {
                            counts[signwriting] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 122888) {
                      if (ch < 122661) {
                        if (ch < 122624) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 122655) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 122880) {
                          if (ch < 122667) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 122887) {
                            counts[glagolitic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 122914) {
                        if (ch < 122905) {
                          counts[glagolitic] += 1;
                        } else {
                          if (ch < 122907) {
                            counts[unknown] += 1;
                          } else {
                            counts[glagolitic] += 1;
                          }
                        }
                      } else {
                        if (ch < 122917) {
                          if (ch < 122915) {
                            counts[unknown] += 1;
                          } else {
                            counts[glagolitic] += 1;
                          }
                        } else {
                          if (ch < 122918) {
                            counts[unknown] += 1;
                          } else {
                            counts[glagolitic] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 126620) {
              if (ch < 126500) {
                if (ch < 124903) {
                  if (ch < 123536) {
                    if (ch < 123181) {
                      if (ch < 123023) {
                        if (ch < 122928) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 122990) {
                            counts[cyrillic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 123024) {
                          counts[cyrillic] += 1;
                        } else {
                          if (ch < 123136) {
                            counts[unknown] += 1;
                          } else {
                            counts[nyiakeng_puachue_hmong] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 123200) {
                        if (ch < 123184) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 123198) {
                            counts[nyiakeng_puachue_hmong] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 123214) {
                          if (ch < 123210) {
                            counts[nyiakeng_puachue_hmong] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 123216) {
                            counts[nyiakeng_puachue_hmong] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 124112) {
                      if (ch < 123642) {
                        if (ch < 123567) {
                          counts[toto] += 1;
                        } else {
                          if (ch < 123584) {
                            counts[unknown] += 1;
                          } else {
                            counts[wancho] += 1;
                          }
                        }
                      } else {
                        if (ch < 123647) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 123648) {
                            counts[wancho] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 124411) {
                        if (ch < 124154) {
                          counts[nag_mundari] += 1;
                        } else {
                          if (ch < 124368) {
                            counts[unknown] += 1;
                          } else {
                            counts[ol_onal] += 1;
                          }
                        }
                      } else {
                        if (ch < 124416) {
                          if (ch < 124415) {
                            counts[unknown] += 1;
                          } else {
                            counts[ol_onal] += 1;
                          }
                        } else {
                          if (ch < 124896) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 125264) {
                    if (ch < 124927) {
                      if (ch < 124909) {
                        if (ch < 124904) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 124908) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 124911) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 124912) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 125127) {
                        if (ch < 124928) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 125125) {
                            counts[mende_kikakui] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 125184) {
                          if (ch < 125143) {
                            counts[mende_kikakui] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 125260) {
                            counts[adlam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126270) {
                      if (ch < 125280) {
                        if (ch < 125274) {
                          counts[adlam] += 1;
                        } else {
                          if (ch < 125278) {
                            counts[unknown] += 1;
                          } else {
                            counts[adlam] += 1;
                          }
                        }
                      } else {
                        if (ch < 126133) {
                          if (ch < 126065) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 126209) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126469) {
                        if (ch < 126464) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126468) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126497) {
                          if (ch < 126496) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 126499) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 126551) {
                  if (ch < 126531) {
                    if (ch < 126516) {
                      if (ch < 126504) {
                        if (ch < 126501) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126503) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126505) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126515) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126522) {
                        if (ch < 126520) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126521) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126524) {
                          if (ch < 126523) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        } else {
                          if (ch < 126530) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126540) {
                      if (ch < 126537) {
                        if (ch < 126535) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126536) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126538) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126539) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126545) {
                        if (ch < 126541) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126544) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126548) {
                          if (ch < 126547) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 126549) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 126565) {
                    if (ch < 126557) {
                      if (ch < 126554) {
                        if (ch < 126552) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126553) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126555) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126556) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126560) {
                        if (ch < 126558) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126559) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126563) {
                          if (ch < 126561) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        } else {
                          if (ch < 126564) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126585) {
                      if (ch < 126572) {
                        if (ch < 126567) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126571) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126580) {
                          if (ch < 126579) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 126584) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126591) {
                        if (ch < 126589) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126590) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126602) {
                          if (ch < 126592) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        } else {
                          if (ch < 126603) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 129104) {
                if (ch < 127491) {
                  if (ch < 127136) {
                    if (ch < 126652) {
                      if (ch < 126629) {
                        if (ch < 126625) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126628) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126634) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126635) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126976) {
                        if (ch < 126704) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126706) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 127024) {
                          if (ch < 127020) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 127124) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 127185) {
                      if (ch < 127168) {
                        if (ch < 127151) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127153) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 127169) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127184) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 127406) {
                        if (ch < 127222) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127232) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 127488) {
                          if (ch < 127462) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 127489) {
                            counts[hiragana] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 128752) {
                    if (ch < 127570) {
                      if (ch < 127552) {
                        if (ch < 127504) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127548) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 127561) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127568) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 127744) {
                        if (ch < 127584) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127590) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 128732) {
                          if (ch < 128728) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 128749) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 129004) {
                      if (ch < 128887) {
                        if (ch < 128765) {
                          counts[common] += 1;
                        } else {
                          if (ch < 128768) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 128986) {
                          if (ch < 128891) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 128992) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 129024) {
                        if (ch < 129008) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129009) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 129040) {
                          if (ch < 129036) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 129096) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 129939) {
                  if (ch < 129646) {
                    if (ch < 129200) {
                      if (ch < 129160) {
                        if (ch < 129114) {
                          counts[common] += 1;
                        } else {
                          if (ch < 129120) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 129168) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129198) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 129218) {
                        if (ch < 129212) {
                          counts[common] += 1;
                        } else {
                          if (ch < 129216) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 129620) {
                          if (ch < 129280) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 129632) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 129742) {
                      if (ch < 129664) {
                        if (ch < 129648) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129661) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 129679) {
                          if (ch < 129674) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 129735) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 129770) {
                        if (ch < 129757) {
                          counts[common] += 1;
                        } else {
                          if (ch < 129759) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 129785) {
                          if (ch < 129776) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        } else {
                          if (ch < 129792) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 191472) {
                    if (ch < 177978) {
                      if (ch < 131072) {
                        if (ch < 129940) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 130042) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 173792) {
                          counts[han] += 1;
                        } else {
                          if (ch < 173824) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 178208) {
                        if (ch < 177984) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 178206) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 183984) {
                          if (ch < 183970) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 191457) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 205744) {
                      if (ch < 195102) {
                        if (ch < 192094) {
                          counts[han] += 1;
                        } else {
                          if (ch < 194560) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      } else {
                        if (ch < 201547) {
                          if (ch < 196608) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        } else {
                          if (ch < 201552) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 917536) {
                        if (ch < 917505) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 917506) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 917760) {
                          if (ch < 917632) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        } else {
                          if (ch < 918000) {
                            counts[inherited] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  if (count_ascii)
    printf("%lu\t%s\n", ascii_cnt, "ASCII");
  for (i = 0; i < 171; ++i) {
    if (counts[i] > 0) {
      printf("%lu\t%s\n", counts[i], scripts[i]);
    }
  }

  if (ferror(stdin)) {
    perror("error reading from standard input: ");
    return 1;
  }
  return 0;
}
