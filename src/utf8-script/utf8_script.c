#include <locale.h>
#include <stdio.h>
#include <wchar.h>

enum unicode_script {
  arabic = 0,
  armenian = 1,
  avestan = 2,
  balinese = 3,
  bamum = 4,
  bassa_vah = 5,
  batak = 6,
  bengali = 7,
  bopomofo = 8,
  brahmi = 9,
  braille = 10,
  buginese = 11,
  buhid = 12,
  canadian_aboriginal = 13,
  carian = 14,
  caucasian_albanian = 15,
  chakma = 16,
  cham = 17,
  cherokee = 18,
  common = 19,
  coptic = 20,
  cuneiform = 21,
  cypriot = 22,
  cyrillic = 23,
  deseret = 24,
  devanagari = 25,
  duployan = 26,
  egyptian_hieroglyphs = 27,
  elbasan = 28,
  ethiopic = 29,
  georgian = 30,
  glagolitic = 31,
  gothic = 32,
  grantha = 33,
  greek = 34,
  gujarati = 35,
  gurmukhi = 36,
  han = 37,
  hangul = 38,
  hanunoo = 39,
  hebrew = 40,
  hiragana = 41,
  imperial_aramaic = 42,
  inherited = 43,
  inscriptional_pahlavi = 44,
  inscriptional_parthian = 45,
  javanese = 46,
  kaithi = 47,
  kannada = 48,
  katakana = 49,
  kayah_li = 50,
  kharoshthi = 51,
  khmer = 52,
  khojki = 53,
  khudawadi = 54,
  lao = 55,
  latin = 56,
  lepcha = 57,
  limbu = 58,
  linear_a = 59,
  linear_b = 60,
  lisu = 61,
  lycian = 62,
  lydian = 63,
  mahajani = 64,
  malayalam = 65,
  mandaic = 66,
  manichaean = 67,
  meetei_mayek = 68,
  mende_kikakui = 69,
  meroitic_cursive = 70,
  meroitic_hieroglyphs = 71,
  miao = 72,
  modi = 73,
  mongolian = 74,
  mro = 75,
  myanmar = 76,
  nabataean = 77,
  new_tai_lue = 78,
  nko = 79,
  ogham = 80,
  ol_chiki = 81,
  old_italic = 82,
  old_north_arabian = 83,
  old_permic = 84,
  old_persian = 85,
  old_south_arabian = 86,
  old_turkic = 87,
  oriya = 88,
  osmanya = 89,
  pahawh_hmong = 90,
  palmyrene = 91,
  pau_cin_hau = 92,
  phags_pa = 93,
  phoenician = 94,
  psalter_pahlavi = 95,
  rejang = 96,
  runic = 97,
  samaritan = 98,
  saurashtra = 99,
  sharada = 100,
  shavian = 101,
  siddham = 102,
  sinhala = 103,
  sora_sompeng = 104,
  sundanese = 105,
  syloti_nagri = 106,
  syriac = 107,
  tagalog = 108,
  tagbanwa = 109,
  tai_le = 110,
  tai_tham = 111,
  tai_viet = 112,
  takri = 113,
  tamil = 114,
  telugu = 115,
  thaana = 116,
  thai = 117,
  tibetan = 118,
  tifinagh = 119,
  tirhuta = 120,
  ugaritic = 121,
  unknown = 122,
  vai = 123,
  warang_citi = 124,
  yi = 125,
};

char *scripts[] = {
  "Arabic",
  "Armenian",
  "Avestan",
  "Balinese",
  "Bamum",
  "Bassa_Vah",
  "Batak",
  "Bengali",
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
  "Common",
  "Coptic",
  "Cuneiform",
  "Cypriot",
  "Cyrillic",
  "Deseret",
  "Devanagari",
  "Duployan",
  "Egyptian_Hieroglyphs",
  "Elbasan",
  "Ethiopic",
  "Georgian",
  "Glagolitic",
  "Gothic",
  "Grantha",
  "Greek",
  "Gujarati",
  "Gurmukhi",
  "Han",
  "Hangul",
  "Hanunoo",
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
  "Kayah_Li",
  "Kharoshthi",
  "Khmer",
  "Khojki",
  "Khudawadi",
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
  "Malayalam",
  "Mandaic",
  "Manichaean",
  "Meetei_Mayek",
  "Mende_Kikakui",
  "Meroitic_Cursive",
  "Meroitic_Hieroglyphs",
  "Miao",
  "Modi",
  "Mongolian",
  "Mro",
  "Myanmar",
  "Nabataean",
  "New_Tai_Lue",
  "Nko",
  "Ogham",
  "Ol_Chiki",
  "Old_Italic",
  "Old_North_Arabian",
  "Old_Permic",
  "Old_Persian",
  "Old_South_Arabian",
  "Old_Turkic",
  "Oriya",
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
  "Sinhala",
  "Sora_Sompeng",
  "Sundanese",
  "Syloti_Nagri",
  "Syriac",
  "Tagalog",
  "Tagbanwa",
  "Tai_Le",
  "Tai_Tham",
  "Tai_Viet",
  "Takri",
  "Tamil",
  "Telugu",
  "Thaana",
  "Thai",
  "Tibetan",
  "Tifinagh",
  "Tirhuta",
  "Ugaritic",
  "Unknown",
  "Vai",
  "Warang_Citi",
  "Yi"
};

int
main(int argc, char **argv) {
  wchar_t ch;
  size_t counts[126];

  int i;
  for (i = 0; i < 126; ++i) {
    counts[i] = 0;
  }

  setlocale(LC_ALL, "");

  while ((ch = getwchar()) != WEOF) {
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
      if (ch < 12032) {
        if (ch < 3585) {
          if (ch < 2740) {
            if (ch < 2043) {
              if (ch < 1369) {
                if (ch < 894) {
                  if (ch < 697) {
                    if (ch < 192) {
                      if (ch < 171) {
                        if (ch < 170) {
                          counts[common] += 1;
                        } else {
                          counts[latin] += 1;
                        }
                      } else {
                        if (ch < 186) {
                          counts[common] += 1;
                        } else {
                          if (ch < 187) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 216) {
                        if (ch < 215) {
                          counts[latin] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 247) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 248) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 768) {
                      if (ch < 741) {
                        if (ch < 736) {
                          counts[common] += 1;
                        } else {
                          counts[latin] += 1;
                        }
                      } else {
                        if (ch < 746) {
                          counts[common] += 1;
                        } else {
                          if (ch < 748) {
                            counts[bopomofo] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 885) {
                        if (ch < 880) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 884) {
                            counts[greek] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 888) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 890) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 910) {
                    if (ch < 902) {
                      if (ch < 896) {
                        if (ch < 895) {
                          counts[common] += 1;
                        } else {
                          counts[greek] += 1;
                        }
                      } else {
                        if (ch < 900) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 901) {
                            counts[greek] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
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
                    }
                  } else {
                    if (ch < 1024) {
                      if (ch < 931) {
                        if (ch < 930) {
                          counts[greek] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 994) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 1008) {
                            counts[coptic] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1328) {
                        if (ch < 1157) {
                          counts[cyrillic] += 1;
                        } else {
                          if (ch < 1159) {
                            counts[inherited] += 1;
                          } else {
                            counts[cyrillic] += 1;
                          }
                        }
                      } else {
                        if (ch < 1329) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 1367) {
                            counts[armenian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 1566) {
                  if (ch < 1488) {
                    if (ch < 1418) {
                      if (ch < 1377) {
                        if (ch < 1376) {
                          counts[armenian] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 1416) {
                          counts[armenian] += 1;
                        } else {
                          if (ch < 1417) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1424) {
                        if (ch < 1419) {
                          counts[armenian] += 1;
                        } else {
                          if (ch < 1421) {
                            counts[unknown] += 1;
                          } else {
                            counts[armenian] += 1;
                          }
                        }
                      } else {
                        if (ch < 1425) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 1480) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1541) {
                      if (ch < 1520) {
                        if (ch < 1515) {
                          counts[hebrew] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 1525) {
                          counts[hebrew] += 1;
                        } else {
                          if (ch < 1536) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1549) {
                        if (ch < 1542) {
                          counts[common] += 1;
                        } else {
                          if (ch < 1548) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 1563) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1565) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 1757) {
                    if (ch < 1611) {
                      if (ch < 1568) {
                        if (ch < 1567) {
                          counts[arabic] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 1600) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1601) {
                            counts[common] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1642) {
                        if (ch < 1622) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 1632) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 1648) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1649) {
                            counts[inherited] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1867) {
                      if (ch < 1792) {
                        if (ch < 1758) {
                          counts[common] += 1;
                        } else {
                          counts[arabic] += 1;
                        }
                      } else {
                        if (ch < 1806) {
                          counts[syriac] += 1;
                        } else {
                          if (ch < 1807) {
                            counts[unknown] += 1;
                          } else {
                            counts[syriac] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1920) {
                        if (ch < 1869) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 1872) {
                            counts[syriac] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 1970) {
                          counts[thaana] += 1;
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
                }
              }
            } else {
              if (ch < 2556) {
                if (ch < 2449) {
                  if (ch < 2276) {
                    if (ch < 2112) {
                      if (ch < 2094) {
                        if (ch < 2048) {
                          counts[unknown] += 1;
                        } else {
                          counts[samaritan] += 1;
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
                        if (ch < 2208) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2227) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2406) {
                      if (ch < 2385) {
                        if (ch < 2304) {
                          counts[arabic] += 1;
                        } else {
                          counts[devanagari] += 1;
                        }
                      } else {
                        if (ch < 2387) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 2404) {
                            counts[devanagari] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2437) {
                        if (ch < 2432) {
                          counts[devanagari] += 1;
                        } else {
                          if (ch < 2436) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2445) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2447) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2503) {
                    if (ch < 2482) {
                      if (ch < 2473) {
                        if (ch < 2451) {
                          counts[unknown] += 1;
                        } else {
                          counts[bengali] += 1;
                        }
                      } else {
                        if (ch < 2474) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2481) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2490) {
                        if (ch < 2483) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2486) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      } else {
                        if (ch < 2492) {
                          counts[unknown] += 1;
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
                    if (ch < 2520) {
                      if (ch < 2507) {
                        if (ch < 2505) {
                          counts[bengali] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 2511) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2519) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2527) {
                        if (ch < 2524) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2526) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2532) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2534) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 2633) {
                  if (ch < 2610) {
                    if (ch < 2575) {
                      if (ch < 2564) {
                        if (ch < 2561) {
                          counts[unknown] += 1;
                        } else {
                          counts[gurmukhi] += 1;
                        }
                      } else {
                        if (ch < 2565) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2571) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2601) {
                        if (ch < 2577) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2579) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      } else {
                        if (ch < 2602) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2609) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2618) {
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
                          if (ch < 2616) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2622) {
                        if (ch < 2620) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2621) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2627) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2631) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2689) {
                    if (ch < 2649) {
                      if (ch < 2638) {
                        if (ch < 2635) {
                          counts[unknown] += 1;
                        } else {
                          counts[gurmukhi] += 1;
                        }
                      } else {
                        if (ch < 2641) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2642) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2655) {
                        if (ch < 2653) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2654) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      } else {
                        if (ch < 2662) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2678) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2706) {
                      if (ch < 2693) {
                        if (ch < 2692) {
                          counts[gujarati] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 2702) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2703) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2730) {
                        if (ch < 2707) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2729) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2737) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2738) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 3142) {
              if (ch < 2946) {
                if (ch < 2835) {
                  if (ch < 2769) {
                    if (ch < 2759) {
                      if (ch < 2746) {
                        if (ch < 2741) {
                          counts[unknown] += 1;
                        } else {
                          counts[gujarati] += 1;
                        }
                      } else {
                        if (ch < 2748) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2758) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2763) {
                        if (ch < 2762) {
                          counts[gujarati] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 2766) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2768) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2817) {
                      if (ch < 2788) {
                        if (ch < 2784) {
                          counts[unknown] += 1;
                        } else {
                          counts[gujarati] += 1;
                        }
                      } else {
                        if (ch < 2790) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2802) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2829) {
                        if (ch < 2820) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2821) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      } else {
                        if (ch < 2831) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2833) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2889) {
                    if (ch < 2868) {
                      if (ch < 2858) {
                        if (ch < 2857) {
                          counts[oriya] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 2865) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2866) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2876) {
                        if (ch < 2869) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2874) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2885) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2887) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2908) {
                      if (ch < 2894) {
                        if (ch < 2891) {
                          counts[unknown] += 1;
                        } else {
                          counts[oriya] += 1;
                        }
                      } else {
                        if (ch < 2902) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2904) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
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
                    }
                  }
                }
              } else {
                if (ch < 3014) {
                  if (ch < 2973) {
                    if (ch < 2961) {
                      if (ch < 2949) {
                        if (ch < 2948) {
                          counts[tamil] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 2955) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 2958) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2969) {
                        if (ch < 2962) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2966) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2971) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 2972) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2984) {
                      if (ch < 2976) {
                        if (ch < 2974) {
                          counts[unknown] += 1;
                        } else {
                          counts[tamil] += 1;
                        }
                      } else {
                        if (ch < 2979) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2981) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3002) {
                        if (ch < 2987) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 2990) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      } else {
                        if (ch < 3006) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3011) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3076) {
                    if (ch < 3025) {
                      if (ch < 3018) {
                        if (ch < 3017) {
                          counts[tamil] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3022) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 3024) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3046) {
                        if (ch < 3031) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3032) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3067) {
                          counts[tamil] += 1;
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
                    if (ch < 3090) {
                      if (ch < 3085) {
                        if (ch < 3077) {
                          counts[unknown] += 1;
                        } else {
                          counts[telugu] += 1;
                        }
                      } else {
                        if (ch < 3086) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3089) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3130) {
                        if (ch < 3113) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3114) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      } else {
                        if (ch < 3133) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3141) {
                            counts[telugu] += 1;
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
              if (ch < 3333) {
                if (ch < 3242) {
                  if (ch < 3184) {
                    if (ch < 3159) {
                      if (ch < 3146) {
                        if (ch < 3145) {
                          counts[telugu] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3150) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3157) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3168) {
                        if (ch < 3160) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3162) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3172) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3174) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3205) {
                      if (ch < 3200) {
                        if (ch < 3192) {
                          counts[unknown] += 1;
                        } else {
                          counts[telugu] += 1;
                        }
                      } else {
                        if (ch < 3201) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3204) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3217) {
                        if (ch < 3213) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3214) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      } else {
                        if (ch < 3218) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3241) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3287) {
                    if (ch < 3269) {
                      if (ch < 3253) {
                        if (ch < 3252) {
                          counts[kannada] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3258) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3260) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3274) {
                        if (ch < 3270) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3273) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3278) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3285) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3302) {
                      if (ch < 3295) {
                        if (ch < 3294) {
                          counts[unknown] += 1;
                        } else {
                          counts[kannada] += 1;
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
                      if (ch < 3315) {
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
                        if (ch < 3329) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3332) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 3461) {
                  if (ch < 3407) {
                    if (ch < 3387) {
                      if (ch < 3342) {
                        if (ch < 3341) {
                          counts[malayalam] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3345) {
                          counts[malayalam] += 1;
                        } else {
                          if (ch < 3346) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3398) {
                        if (ch < 3389) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3397) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3401) {
                          counts[malayalam] += 1;
                        } else {
                          if (ch < 3402) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3430) {
                      if (ch < 3416) {
                        if (ch < 3415) {
                          counts[unknown] += 1;
                        } else {
                          counts[malayalam] += 1;
                        }
                      } else {
                        if (ch < 3424) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3428) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3456) {
                        if (ch < 3446) {
                          counts[malayalam] += 1;
                        } else {
                          if (ch < 3449) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        }
                      } else {
                        if (ch < 3458) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3460) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3531) {
                    if (ch < 3516) {
                      if (ch < 3482) {
                        if (ch < 3479) {
                          counts[sinhala] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3506) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3507) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3520) {
                        if (ch < 3517) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3518) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3527) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3530) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3544) {
                      if (ch < 3541) {
                        if (ch < 3535) {
                          counts[unknown] += 1;
                        } else {
                          counts[sinhala] += 1;
                        }
                      } else {
                        if (ch < 3542) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3543) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3568) {
                        if (ch < 3552) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3558) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      } else {
                        if (ch < 3570) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3573) {
                            counts[sinhala] += 1;
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
          if (ch < 6794) {
            if (ch < 4801) {
              if (ch < 3913) {
                if (ch < 3749) {
                  if (ch < 3721) {
                    if (ch < 3713) {
                      if (ch < 3647) {
                        if (ch < 3643) {
                          counts[thai] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3648) {
                          counts[common] += 1;
                        } else {
                          if (ch < 3676) {
                            counts[thai] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3716) {
                        if (ch < 3715) {
                          counts[lao] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3717) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3719) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3732) {
                      if (ch < 3723) {
                        if (ch < 3722) {
                          counts[unknown] += 1;
                        } else {
                          counts[lao] += 1;
                        }
                      } else {
                        if (ch < 3725) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3726) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3744) {
                        if (ch < 3736) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3737) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      } else {
                        if (ch < 3745) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3748) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3781) {
                    if (ch < 3756) {
                      if (ch < 3751) {
                        if (ch < 3750) {
                          counts[lao] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3752) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3754) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3771) {
                        if (ch < 3757) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3770) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3774) {
                          counts[lao] += 1;
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
                    if (ch < 3792) {
                      if (ch < 3783) {
                        if (ch < 3782) {
                          counts[unknown] += 1;
                        } else {
                          counts[lao] += 1;
                        }
                      } else {
                        if (ch < 3784) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3790) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3808) {
                        if (ch < 3802) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3804) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      } else {
                        if (ch < 3840) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3912) {
                            counts[tibetan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 4352) {
                  if (ch < 4059) {
                    if (ch < 4029) {
                      if (ch < 3953) {
                        if (ch < 3949) {
                          counts[tibetan] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3992) {
                          counts[tibetan] += 1;
                        } else {
                          if (ch < 3993) {
                            counts[unknown] += 1;
                          } else {
                            counts[tibetan] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4046) {
                        if (ch < 4030) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4045) {
                            counts[tibetan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4053) {
                          counts[tibetan] += 1;
                        } else {
                          if (ch < 4057) {
                            counts[common] += 1;
                          } else {
                            counts[tibetan] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4296) {
                      if (ch < 4256) {
                        if (ch < 4096) {
                          counts[unknown] += 1;
                        } else {
                          counts[myanmar] += 1;
                        }
                      } else {
                        if (ch < 4294) {
                          counts[georgian] += 1;
                        } else {
                          if (ch < 4295) {
                            counts[unknown] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      }
                    } else {
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
                        if (ch < 4347) {
                          counts[georgian] += 1;
                        } else {
                          if (ch < 4348) {
                            counts[common] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 4704) {
                    if (ch < 4688) {
                      if (ch < 4681) {
                        if (ch < 4608) {
                          counts[hangul] += 1;
                        } else {
                          counts[ethiopic] += 1;
                        }
                      } else {
                        if (ch < 4682) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4686) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4697) {
                        if (ch < 4695) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4696) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 4698) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4702) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4785) {
                      if (ch < 4746) {
                        if (ch < 4745) {
                          counts[ethiopic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 4750) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4752) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4792) {
                        if (ch < 4786) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4790) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4799) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4800) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 6138) {
                if (ch < 5870) {
                  if (ch < 4957) {
                    if (ch < 4824) {
                      if (ch < 4806) {
                        if (ch < 4802) {
                          counts[unknown] += 1;
                        } else {
                          counts[ethiopic] += 1;
                        }
                      } else {
                        if (ch < 4808) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4823) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4886) {
                        if (ch < 4881) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4882) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 4888) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4955) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 5109) {
                      if (ch < 4992) {
                        if (ch < 4989) {
                          counts[ethiopic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 5018) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 5024) {
                            counts[unknown] += 1;
                          } else {
                            counts[cherokee] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 5789) {
                        if (ch < 5120) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 5760) {
                            counts[canadian_aboriginal] += 1;
                          } else {
                            counts[ogham] += 1;
                          }
                        }
                      } else {
                        if (ch < 5792) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 5867) {
                            counts[runic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 5984) {
                    if (ch < 5909) {
                      if (ch < 5888) {
                        if (ch < 5881) {
                          counts[runic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 5901) {
                          counts[tagalog] += 1;
                        } else {
                          if (ch < 5902) {
                            counts[unknown] += 1;
                          } else {
                            counts[tagalog] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 5943) {
                        if (ch < 5920) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 5941) {
                            counts[hanunoo] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 5952) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 5972) {
                            counts[buhid] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6004) {
                      if (ch < 5998) {
                        if (ch < 5997) {
                          counts[tagbanwa] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 6001) {
                          counts[tagbanwa] += 1;
                        } else {
                          if (ch < 6002) {
                            counts[unknown] += 1;
                          } else {
                            counts[tagbanwa] += 1;
                          }
                        }
                      }
                    } else {
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
                    }
                  }
                }
              } else {
                if (ch < 6465) {
                  if (ch < 6272) {
                    if (ch < 6150) {
                      if (ch < 6146) {
                        if (ch < 6144) {
                          counts[unknown] += 1;
                        } else {
                          counts[mongolian] += 1;
                        }
                      } else {
                        if (ch < 6148) {
                          counts[common] += 1;
                        } else {
                          if (ch < 6149) {
                            counts[mongolian] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6170) {
                        if (ch < 6159) {
                          counts[mongolian] += 1;
                        } else {
                          if (ch < 6160) {
                            counts[unknown] += 1;
                          } else {
                            counts[mongolian] += 1;
                          }
                        }
                      } else {
                        if (ch < 6176) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6264) {
                            counts[mongolian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6431) {
                      if (ch < 6320) {
                        if (ch < 6315) {
                          counts[mongolian] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 6390) {
                          counts[canadian_aboriginal] += 1;
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
                        if (ch < 6460) {
                          counts[limbu] += 1;
                        } else {
                          if (ch < 6464) {
                            counts[unknown] += 1;
                          } else {
                            counts[limbu] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 6619) {
                    if (ch < 6517) {
                      if (ch < 6480) {
                        if (ch < 6468) {
                          counts[unknown] += 1;
                        } else {
                          counts[limbu] += 1;
                        }
                      } else {
                        if (ch < 6510) {
                          counts[tai_le] += 1;
                        } else {
                          if (ch < 6512) {
                            counts[unknown] += 1;
                          } else {
                            counts[tai_le] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6576) {
                        if (ch < 6528) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6572) {
                            counts[new_tai_lue] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6602) {
                          counts[new_tai_lue] += 1;
                        } else {
                          if (ch < 6608) {
                            counts[unknown] += 1;
                          } else {
                            counts[new_tai_lue] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6686) {
                      if (ch < 6624) {
                        if (ch < 6622) {
                          counts[unknown] += 1;
                        } else {
                          counts[new_tai_lue] += 1;
                        }
                      } else {
                        if (ch < 6656) {
                          counts[khmer] += 1;
                        } else {
                          if (ch < 6684) {
                            counts[buginese] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6752) {
                        if (ch < 6688) {
                          counts[buginese] += 1;
                        } else {
                          if (ch < 6751) {
                            counts[tai_tham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6781) {
                          counts[tai_tham] += 1;
                        } else {
                          if (ch < 6783) {
                            counts[unknown] += 1;
                          } else {
                            counts[tai_tham] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 8293) {
              if (ch < 7526) {
                if (ch < 7296) {
                  if (ch < 7037) {
                    if (ch < 6832) {
                      if (ch < 6810) {
                        if (ch < 6800) {
                          counts[unknown] += 1;
                        } else {
                          counts[tai_tham] += 1;
                        }
                      } else {
                        if (ch < 6816) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6830) {
                            counts[tai_tham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6912) {
                        if (ch < 6847) {
                          counts[inherited] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 6988) {
                          counts[balinese] += 1;
                        } else {
                          if (ch < 6992) {
                            counts[unknown] += 1;
                          } else {
                            counts[balinese] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7168) {
                      if (ch < 7104) {
                        if (ch < 7040) {
                          counts[unknown] += 1;
                        } else {
                          counts[sundanese] += 1;
                        }
                      } else {
                        if (ch < 7156) {
                          counts[batak] += 1;
                        } else {
                          if (ch < 7164) {
                            counts[unknown] += 1;
                          } else {
                            counts[batak] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7242) {
                        if (ch < 7224) {
                          counts[lepcha] += 1;
                        } else {
                          if (ch < 7227) {
                            counts[unknown] += 1;
                          } else {
                            counts[lepcha] += 1;
                          }
                        }
                      } else {
                        if (ch < 7245) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 7248) {
                            counts[lepcha] += 1;
                          } else {
                            counts[ol_chiki] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 7412) {
                    if (ch < 7380) {
                      if (ch < 7368) {
                        if (ch < 7360) {
                          counts[unknown] += 1;
                        } else {
                          counts[sundanese] += 1;
                        }
                      } else {
                        if (ch < 7376) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 7379) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7401) {
                        if (ch < 7393) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 7394) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 7405) {
                          counts[common] += 1;
                        } else {
                          if (ch < 7406) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7424) {
                      if (ch < 7415) {
                        if (ch < 7413) {
                          counts[inherited] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 7416) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 7418) {
                            counts[inherited] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7468) {
                        if (ch < 7462) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 7467) {
                            counts[greek] += 1;
                          } else {
                            counts[cyrillic] += 1;
                          }
                        }
                      } else {
                        if (ch < 7517) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 7522) {
                            counts[greek] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 8028) {
                  if (ch < 7960) {
                    if (ch < 7616) {
                      if (ch < 7544) {
                        if (ch < 7531) {
                          counts[greek] += 1;
                        } else {
                          counts[latin] += 1;
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
                      if (ch < 7680) {
                        if (ch < 7670) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 7676) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 7936) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 7958) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8014) {
                      if (ch < 7968) {
                        if (ch < 7966) {
                          counts[greek] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 8006) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8008) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8025) {
                        if (ch < 8016) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8024) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 8026) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8027) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 8150) {
                    if (ch < 8064) {
                      if (ch < 8030) {
                        if (ch < 8029) {
                          counts[unknown] += 1;
                        } else {
                          counts[greek] += 1;
                        }
                      } else {
                        if (ch < 8031) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8062) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
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
                        if (ch < 8134) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8148) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8181) {
                      if (ch < 8157) {
                        if (ch < 8156) {
                          counts[greek] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 8176) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8178) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8192) {
                        if (ch < 8182) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8191) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 8204) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8206) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 11264) {
                if (ch < 8527) {
                  if (ch < 8382) {
                    if (ch < 8319) {
                      if (ch < 8305) {
                        if (ch < 8294) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 8306) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 8308) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8336) {
                        if (ch < 8320) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 8335) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 8349) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 8352) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8487) {
                      if (ch < 8433) {
                        if (ch < 8400) {
                          counts[unknown] += 1;
                        } else {
                          counts[inherited] += 1;
                        }
                      } else {
                        if (ch < 8448) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8486) {
                            counts[common] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8498) {
                        if (ch < 8490) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8492) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 8499) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 8526) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 10240) {
                    if (ch < 9211) {
                      if (ch < 8585) {
                        if (ch < 8544) {
                          counts[common] += 1;
                        } else {
                          counts[latin] += 1;
                        }
                      } else {
                        if (ch < 8586) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8592) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 9280) {
                        if (ch < 9216) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 9255) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 9291) {
                          counts[common] += 1;
                        } else {
                          if (ch < 9312) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11160) {
                      if (ch < 11124) {
                        if (ch < 10496) {
                          counts[braille] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 11126) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11158) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11209) {
                        if (ch < 11194) {
                          counts[common] += 1;
                        } else {
                          if (ch < 11197) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 11210) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11218) {
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
                if (ch < 11687) {
                  if (ch < 11560) {
                    if (ch < 11392) {
                      if (ch < 11312) {
                        if (ch < 11311) {
                          counts[glagolitic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 11359) {
                          counts[glagolitic] += 1;
                        } else {
                          if (ch < 11360) {
                            counts[unknown] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11520) {
                        if (ch < 11508) {
                          counts[coptic] += 1;
                        } else {
                          if (ch < 11513) {
                            counts[unknown] += 1;
                          } else {
                            counts[coptic] += 1;
                          }
                        }
                      } else {
                        if (ch < 11558) {
                          counts[georgian] += 1;
                        } else {
                          if (ch < 11559) {
                            counts[unknown] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11631) {
                      if (ch < 11566) {
                        if (ch < 11565) {
                          counts[unknown] += 1;
                        } else {
                          counts[georgian] += 1;
                        }
                      } else {
                        if (ch < 11568) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11624) {
                            counts[tifinagh] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11648) {
                        if (ch < 11633) {
                          counts[tifinagh] += 1;
                        } else {
                          if (ch < 11647) {
                            counts[unknown] += 1;
                          } else {
                            counts[tifinagh] += 1;
                          }
                        }
                      } else {
                        if (ch < 11671) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 11680) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11728) {
                    if (ch < 11704) {
                      if (ch < 11695) {
                        if (ch < 11688) {
                          counts[unknown] += 1;
                        } else {
                          counts[ethiopic] += 1;
                        }
                      } else {
                        if (ch < 11696) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11703) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11719) {
                        if (ch < 11711) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 11712) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 11720) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11727) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11776) {
                      if (ch < 11736) {
                        if (ch < 11735) {
                          counts[ethiopic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 11743) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 11744) {
                            counts[unknown] += 1;
                          } else {
                            counts[cyrillic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11930) {
                        if (ch < 11843) {
                          counts[common] += 1;
                        } else {
                          if (ch < 11904) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      } else {
                        if (ch < 11931) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12020) {
                            counts[han] += 1;
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
      } else {
        if (ch < 69247) {
          if (ch < 65072) {
            if (ch < 43312) {
              if (ch < 13056) {
                if (ch < 12448) {
                  if (ch < 12330) {
                    if (ch < 12293) {
                      if (ch < 12272) {
                        if (ch < 12246) {
                          counts[han] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 12284) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12288) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12295) {
                        if (ch < 12294) {
                          counts[han] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 12296) {
                          counts[han] += 1;
                        } else {
                          if (ch < 12321) {
                            counts[common] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12352) {
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
                          if (ch < 12348) {
                            counts[han] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12441) {
                        if (ch < 12353) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12439) {
                            counts[hiragana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 12443) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 12445) {
                            counts[common] += 1;
                          } else {
                            counts[hiragana] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 12731) {
                    if (ch < 12549) {
                      if (ch < 12539) {
                        if (ch < 12449) {
                          counts[common] += 1;
                        } else {
                          counts[katakana] += 1;
                        }
                      } else {
                        if (ch < 12541) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12544) {
                            counts[katakana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12687) {
                        if (ch < 12590) {
                          counts[bopomofo] += 1;
                        } else {
                          if (ch < 12593) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      } else {
                        if (ch < 12688) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12704) {
                            counts[common] += 1;
                          } else {
                            counts[bopomofo] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12831) {
                      if (ch < 12772) {
                        if (ch < 12736) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 12784) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12800) {
                            counts[katakana] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12927) {
                        if (ch < 12832) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12896) {
                            counts[common] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      } else {
                        if (ch < 13008) {
                          counts[common] += 1;
                        } else {
                          if (ch < 13055) {
                            counts[katakana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 42891) {
                  if (ch < 42192) {
                    if (ch < 19968) {
                      if (ch < 13312) {
                        if (ch < 13144) {
                          counts[katakana] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 19894) {
                          counts[han] += 1;
                        } else {
                          if (ch < 19904) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 42125) {
                        if (ch < 40909) {
                          counts[han] += 1;
                        } else {
                          if (ch < 40960) {
                            counts[unknown] += 1;
                          } else {
                            counts[yi] += 1;
                          }
                        }
                      } else {
                        if (ch < 42128) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 42183) {
                            counts[yi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42655) {
                      if (ch < 42540) {
                        if (ch < 42240) {
                          counts[lisu] += 1;
                        } else {
                          counts[vai] += 1;
                        }
                      } else {
                        if (ch < 42560) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 42654) {
                            counts[cyrillic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 42752) {
                        if (ch < 42656) {
                          counts[cyrillic] += 1;
                        } else {
                          if (ch < 42744) {
                            counts[bamum] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 42786) {
                          counts[common] += 1;
                        } else {
                          if (ch < 42888) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 43072) {
                    if (ch < 42930) {
                      if (ch < 42896) {
                        if (ch < 42895) {
                          counts[latin] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 42926) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 42928) {
                            counts[unknown] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43052) {
                        if (ch < 42999) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43008) {
                            counts[latin] += 1;
                          } else {
                            counts[syloti_nagri] += 1;
                          }
                        }
                      } else {
                        if (ch < 43056) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43066) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43226) {
                      if (ch < 43136) {
                        if (ch < 43128) {
                          counts[phags_pa] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 43205) {
                          counts[saurashtra] += 1;
                        } else {
                          if (ch < 43214) {
                            counts[unknown] += 1;
                          } else {
                            counts[saurashtra] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43264) {
                        if (ch < 43232) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43260) {
                            counts[devanagari] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 43310) {
                          counts[kayah_li] += 1;
                        } else {
                          if (ch < 43311) {
                            counts[common] += 1;
                          } else {
                            counts[kayah_li] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 44014) {
                if (ch < 43715) {
                  if (ch < 43488) {
                    if (ch < 43392) {
                      if (ch < 43359) {
                        if (ch < 43348) {
                          counts[rejang] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 43360) {
                          counts[rejang] += 1;
                        } else {
                          if (ch < 43389) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43472) {
                        if (ch < 43470) {
                          counts[javanese] += 1;
                        } else {
                          if (ch < 43471) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 43482) {
                          counts[javanese] += 1;
                        } else {
                          if (ch < 43486) {
                            counts[unknown] += 1;
                          } else {
                            counts[javanese] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43598) {
                      if (ch < 43520) {
                        if (ch < 43519) {
                          counts[myanmar] += 1;
                        } else {
                          counts[unknown] += 1;
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
                        if (ch < 43616) {
                          counts[cham] += 1;
                        } else {
                          if (ch < 43648) {
                            counts[myanmar] += 1;
                          } else {
                            counts[tai_viet] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 43815) {
                    if (ch < 43783) {
                      if (ch < 43744) {
                        if (ch < 43739) {
                          counts[unknown] += 1;
                        } else {
                          counts[tai_viet] += 1;
                        }
                      } else {
                        if (ch < 43767) {
                          counts[meetei_mayek] += 1;
                        } else {
                          if (ch < 43777) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43793) {
                        if (ch < 43785) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43791) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 43799) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 43808) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43868) {
                      if (ch < 43823) {
                        if (ch < 43816) {
                          counts[unknown] += 1;
                        } else {
                          counts[ethiopic] += 1;
                        }
                      } else {
                        if (ch < 43824) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43867) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43877) {
                        if (ch < 43872) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 43876) {
                            counts[unknown] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 43878) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 43968) {
                            counts[unknown] += 1;
                          } else {
                            counts[meetei_mayek] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 64319) {
                  if (ch < 64112) {
                    if (ch < 55216) {
                      if (ch < 44026) {
                        if (ch < 44016) {
                          counts[unknown] += 1;
                        } else {
                          counts[meetei_mayek] += 1;
                        }
                      } else {
                        if (ch < 44032) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 55204) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
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
                    }
                  } else {
                    if (ch < 64280) {
                      if (ch < 64256) {
                        if (ch < 64218) {
                          counts[han] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 64263) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 64275) {
                            counts[unknown] += 1;
                          } else {
                            counts[armenian] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 64312) {
                        if (ch < 64285) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64311) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 64317) {
                          counts[hebrew] += 1;
                        } else {
                          if (ch < 64318) {
                            counts[unknown] += 1;
                          } else {
                            counts[hebrew] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 64848) {
                    if (ch < 64326) {
                      if (ch < 64322) {
                        if (ch < 64320) {
                          counts[unknown] += 1;
                        } else {
                          counts[hebrew] += 1;
                        }
                      } else {
                        if (ch < 64323) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64325) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 64467) {
                        if (ch < 64336) {
                          counts[hebrew] += 1;
                        } else {
                          if (ch < 64450) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 64830) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 64832) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65022) {
                      if (ch < 64914) {
                        if (ch < 64912) {
                          counts[arabic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 64968) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 65008) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65050) {
                        if (ch < 65024) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65040) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65056) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65070) {
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
          } else {
            if (ch < 66688) {
              if (ch < 65596) {
                if (ch < 65440) {
                  if (ch < 65279) {
                    if (ch < 65132) {
                      if (ch < 65108) {
                        if (ch < 65107) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 65127) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65128) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65141) {
                        if (ch < 65136) {
                          counts[unknown] += 1;
                        } else {
                          counts[arabic] += 1;
                        }
                      } else {
                        if (ch < 65142) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65277) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65345) {
                      if (ch < 65281) {
                        if (ch < 65280) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 65313) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65339) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
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
                    }
                  }
                } else {
                  if (ch < 65511) {
                    if (ch < 65488) {
                      if (ch < 65474) {
                        if (ch < 65471) {
                          counts[hangul] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 65480) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 65482) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65498) {
                        if (ch < 65490) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65496) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 65501) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 65504) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65536) {
                      if (ch < 65519) {
                        if (ch < 65512) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 65529) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65534) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65575) {
                        if (ch < 65548) {
                          counts[linear_b] += 1;
                        } else {
                          if (ch < 65549) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_b] += 1;
                          }
                        }
                      } else {
                        if (ch < 65576) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65595) {
                            counts[linear_b] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 66176) {
                  if (ch < 65844) {
                    if (ch < 65630) {
                      if (ch < 65599) {
                        if (ch < 65598) {
                          counts[linear_b] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 65614) {
                          counts[linear_b] += 1;
                        } else {
                          if (ch < 65616) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_b] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65792) {
                        if (ch < 65664) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65787) {
                            counts[linear_b] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 65795) {
                          counts[common] += 1;
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
                    if (ch < 65948) {
                      if (ch < 65856) {
                        if (ch < 65847) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 65933) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 65936) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66000) {
                        if (ch < 65952) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65953) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 66045) {
                          counts[common] += 1;
                        } else {
                          if (ch < 66046) {
                            counts[inherited] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 66384) {
                    if (ch < 66273) {
                      if (ch < 66208) {
                        if (ch < 66205) {
                          counts[lycian] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 66257) {
                          counts[carian] += 1;
                        } else {
                          if (ch < 66272) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66340) {
                        if (ch < 66300) {
                          counts[common] += 1;
                        } else {
                          if (ch < 66304) {
                            counts[unknown] += 1;
                          } else {
                            counts[old_italic] += 1;
                          }
                        }
                      } else {
                        if (ch < 66352) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66379) {
                            counts[gothic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 66464) {
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
                          if (ch < 66463) {
                            counts[unknown] += 1;
                          } else {
                            counts[ugaritic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66518) {
                        if (ch < 66500) {
                          counts[old_persian] += 1;
                        } else {
                          if (ch < 66504) {
                            counts[unknown] += 1;
                          } else {
                            counts[old_persian] += 1;
                          }
                        }
                      } else {
                        if (ch < 66560) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66640) {
                            counts[deseret] += 1;
                          } else {
                            counts[shavian] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 68024) {
                if (ch < 67639) {
                  if (ch < 67383) {
                    if (ch < 66856) {
                      if (ch < 66720) {
                        if (ch < 66718) {
                          counts[osmanya] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 66730) {
                          counts[osmanya] += 1;
                        } else {
                          if (ch < 66816) {
                            counts[unknown] += 1;
                          } else {
                            counts[elbasan] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66927) {
                        if (ch < 66864) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66916) {
                            counts[caucasian_albanian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 66928) {
                          counts[caucasian_albanian] += 1;
                        } else {
                          if (ch < 67072) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_a] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 67584) {
                      if (ch < 67414) {
                        if (ch < 67392) {
                          counts[unknown] += 1;
                        } else {
                          counts[linear_a] += 1;
                        }
                      } else {
                        if (ch < 67424) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67432) {
                            counts[linear_a] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67593) {
                        if (ch < 67590) {
                          counts[cypriot] += 1;
                        } else {
                          if (ch < 67592) {
                            counts[unknown] += 1;
                          } else {
                            counts[cypriot] += 1;
                          }
                        }
                      } else {
                        if (ch < 67594) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67638) {
                            counts[cypriot] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 67751) {
                    if (ch < 67648) {
                      if (ch < 67644) {
                        if (ch < 67641) {
                          counts[cypriot] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 67645) {
                          counts[cypriot] += 1;
                        } else {
                          if (ch < 67647) {
                            counts[unknown] += 1;
                          } else {
                            counts[cypriot] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67680) {
                        if (ch < 67670) {
                          counts[imperial_aramaic] += 1;
                        } else {
                          if (ch < 67671) {
                            counts[unknown] += 1;
                          } else {
                            counts[imperial_aramaic] += 1;
                          }
                        }
                      } else {
                        if (ch < 67712) {
                          counts[palmyrene] += 1;
                        } else {
                          if (ch < 67743) {
                            counts[nabataean] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 67872) {
                      if (ch < 67840) {
                        if (ch < 67760) {
                          counts[nabataean] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 67868) {
                          counts[phoenician] += 1;
                        } else {
                          if (ch < 67871) {
                            counts[unknown] += 1;
                          } else {
                            counts[phoenician] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67904) {
                        if (ch < 67898) {
                          counts[lydian] += 1;
                        } else {
                          if (ch < 67903) {
                            counts[unknown] += 1;
                          } else {
                            counts[lydian] += 1;
                          }
                        }
                      } else {
                        if (ch < 67968) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68000) {
                            counts[meroitic_hieroglyphs] += 1;
                          } else {
                            counts[meroitic_cursive] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 68288) {
                  if (ch < 68121) {
                    if (ch < 68101) {
                      if (ch < 68032) {
                        if (ch < 68030) {
                          counts[unknown] += 1;
                        } else {
                          counts[meroitic_cursive] += 1;
                        }
                      } else {
                        if (ch < 68096) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68100) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68116) {
                        if (ch < 68103) {
                          counts[kharoshthi] += 1;
                        } else {
                          if (ch < 68108) {
                            counts[unknown] += 1;
                          } else {
                            counts[kharoshthi] += 1;
                          }
                        }
                      } else {
                        if (ch < 68117) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68120) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 68168) {
                      if (ch < 68152) {
                        if (ch < 68148) {
                          counts[kharoshthi] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 68155) {
                          counts[kharoshthi] += 1;
                        } else {
                          if (ch < 68159) {
                            counts[unknown] += 1;
                          } else {
                            counts[kharoshthi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68192) {
                        if (ch < 68176) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68185) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68224) {
                          counts[old_south_arabian] += 1;
                        } else {
                          if (ch < 68256) {
                            counts[old_north_arabian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 68467) {
                    if (ch < 68406) {
                      if (ch < 68331) {
                        if (ch < 68327) {
                          counts[manichaean] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 68343) {
                          counts[manichaean] += 1;
                        } else {
                          if (ch < 68352) {
                            counts[unknown] += 1;
                          } else {
                            counts[avestan] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68438) {
                        if (ch < 68409) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68416) {
                            counts[avestan] += 1;
                          } else {
                            counts[inscriptional_parthian] += 1;
                          }
                        }
                      } else {
                        if (ch < 68440) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68448) {
                            counts[inscriptional_parthian] += 1;
                          } else {
                            counts[inscriptional_pahlavi] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 68509) {
                      if (ch < 68480) {
                        if (ch < 68472) {
                          counts[unknown] += 1;
                        } else {
                          counts[inscriptional_pahlavi] += 1;
                        }
                      } else {
                        if (ch < 68498) {
                          counts[psalter_pahlavi] += 1;
                        } else {
                          if (ch < 68505) {
                            counts[unknown] += 1;
                          } else {
                            counts[psalter_pahlavi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68608) {
                        if (ch < 68521) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68528) {
                            counts[psalter_pahlavi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68681) {
                          counts[old_turkic] += 1;
                        } else {
                          if (ch < 69216) {
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
            }
          }
        } else {
          if (ch < 120075) {
            if (ch < 74863) {
              if (ch < 70449) {
                if (ch < 70094) {
                  if (ch < 69872) {
                    if (ch < 69759) {
                      if (ch < 69710) {
                        if (ch < 69632) {
                          counts[unknown] += 1;
                        } else {
                          counts[brahmi] += 1;
                        }
                      } else {
                        if (ch < 69714) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 69744) {
                            counts[brahmi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 69826) {
                        if (ch < 69760) {
                          counts[brahmi] += 1;
                        } else {
                          counts[kaithi] += 1;
                        }
                      } else {
                        if (ch < 69840) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 69865) {
                            counts[sora_sompeng] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 69956) {
                      if (ch < 69888) {
                        if (ch < 69882) {
                          counts[sora_sompeng] += 1;
                        } else {
                          counts[unknown] += 1;
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
                        if (ch < 70089) {
                          counts[sharada] += 1;
                        } else {
                          if (ch < 70093) {
                            counts[unknown] += 1;
                          } else {
                            counts[sharada] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 70384) {
                    if (ch < 70144) {
                      if (ch < 70107) {
                        if (ch < 70096) {
                          counts[unknown] += 1;
                        } else {
                          counts[sharada] += 1;
                        }
                      } else {
                        if (ch < 70113) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70133) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70206) {
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
                        if (ch < 70320) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70379) {
                            counts[khudawadi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70413) {
                      if (ch < 70401) {
                        if (ch < 70394) {
                          counts[khudawadi] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 70404) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70405) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70419) {
                        if (ch < 70415) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70417) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 70441) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70442) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 70874) {
                  if (ch < 70487) {
                    if (ch < 70460) {
                      if (ch < 70452) {
                        if (ch < 70450) {
                          counts[unknown] += 1;
                        } else {
                          counts[grantha] += 1;
                        }
                      } else {
                        if (ch < 70453) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70458) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
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
                        if (ch < 70475) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70478) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70509) {
                      if (ch < 70493) {
                        if (ch < 70488) {
                          counts[grantha] += 1;
                        } else {
                          counts[unknown] += 1;
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
                      if (ch < 70784) {
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
                        if (ch < 70856) {
                          counts[tirhuta] += 1;
                        } else {
                          if (ch < 70864) {
                            counts[unknown] += 1;
                          } else {
                            counts[tirhuta] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 71360) {
                    if (ch < 71168) {
                      if (ch < 71094) {
                        if (ch < 71040) {
                          counts[unknown] += 1;
                        } else {
                          counts[siddham] += 1;
                        }
                      } else {
                        if (ch < 71096) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71114) {
                            counts[siddham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 71258) {
                        if (ch < 71237) {
                          counts[modi] += 1;
                        } else {
                          if (ch < 71248) {
                            counts[unknown] += 1;
                          } else {
                            counts[modi] += 1;
                          }
                        }
                      } else {
                        if (ch < 71296) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71352) {
                            counts[takri] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 71936) {
                      if (ch < 71840) {
                        if (ch < 71370) {
                          counts[takri] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 71923) {
                          counts[warang_citi] += 1;
                        } else {
                          if (ch < 71935) {
                            counts[unknown] += 1;
                          } else {
                            counts[warang_citi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 73728) {
                        if (ch < 72384) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 72441) {
                            counts[pau_cin_hau] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 74649) {
                          counts[cuneiform] += 1;
                        } else {
                          if (ch < 74752) {
                            counts[unknown] += 1;
                          } else {
                            counts[cuneiform] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 113820) {
                if (ch < 93026) {
                  if (ch < 92782) {
                    if (ch < 92160) {
                      if (ch < 74869) {
                        if (ch < 74864) {
                          counts[unknown] += 1;
                        } else {
                          counts[cuneiform] += 1;
                        }
                      } else {
                        if (ch < 77824) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 78895) {
                            counts[egyptian_hieroglyphs] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 92767) {
                        if (ch < 92729) {
                          counts[bamum] += 1;
                        } else {
                          if (ch < 92736) {
                            counts[unknown] += 1;
                          } else {
                            counts[mro] += 1;
                          }
                        }
                      } else {
                        if (ch < 92768) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 92778) {
                            counts[mro] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 92918) {
                      if (ch < 92880) {
                        if (ch < 92784) {
                          counts[mro] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 92910) {
                          counts[bassa_vah] += 1;
                        } else {
                          if (ch < 92912) {
                            counts[unknown] += 1;
                          } else {
                            counts[bassa_vah] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 93008) {
                        if (ch < 92928) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 92998) {
                            counts[pahawh_hmong] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 93018) {
                          counts[pahawh_hmong] += 1;
                        } else {
                          if (ch < 93019) {
                            counts[unknown] += 1;
                          } else {
                            counts[pahawh_hmong] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 110592) {
                    if (ch < 93952) {
                      if (ch < 93048) {
                        if (ch < 93027) {
                          counts[unknown] += 1;
                        } else {
                          counts[pahawh_hmong] += 1;
                        }
                      } else {
                        if (ch < 93053) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 93072) {
                            counts[pahawh_hmong] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 94079) {
                        if (ch < 94021) {
                          counts[miao] += 1;
                        } else {
                          if (ch < 94032) {
                            counts[unknown] += 1;
                          } else {
                            counts[miao] += 1;
                          }
                        }
                      } else {
                        if (ch < 94095) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 94112) {
                            counts[miao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 113776) {
                      if (ch < 110594) {
                        if (ch < 110593) {
                          counts[katakana] += 1;
                        } else {
                          counts[hiragana] += 1;
                        }
                      } else {
                        if (ch < 113664) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 113771) {
                            counts[duployan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 113801) {
                        if (ch < 113789) {
                          counts[duployan] += 1;
                        } else {
                          if (ch < 113792) {
                            counts[unknown] += 1;
                          } else {
                            counts[duployan] += 1;
                          }
                        }
                      } else {
                        if (ch < 113808) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 113818) {
                            counts[duployan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 119666) {
                  if (ch < 119171) {
                    if (ch < 119040) {
                      if (ch < 113828) {
                        if (ch < 113824) {
                          counts[duployan] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 118784) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119030) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119143) {
                        if (ch < 119079) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119081) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119146) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 119163) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 119262) {
                      if (ch < 119180) {
                        if (ch < 119173) {
                          counts[common] += 1;
                        } else {
                          counts[inherited] += 1;
                        }
                      } else {
                        if (ch < 119210) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119214) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119552) {
                        if (ch < 119296) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119366) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 119639) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119648) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 119977) {
                    if (ch < 119966) {
                      if (ch < 119893) {
                        if (ch < 119808) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 119894) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119965) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119971) {
                        if (ch < 119968) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119970) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119973) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119975) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 119996) {
                      if (ch < 119982) {
                        if (ch < 119981) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 119994) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119995) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 120005) {
                        if (ch < 119997) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120004) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 120070) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120071) {
                            counts[unknown] += 1;
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
          } else {
            if (ch < 126629) {
              if (ch < 126530) {
                if (ch < 124928) {
                  if (ch < 120133) {
                    if (ch < 120094) {
                      if (ch < 120085) {
                        if (ch < 120077) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 120086) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120093) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 120123) {
                        if (ch < 120122) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 120127) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120128) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 120146) {
                      if (ch < 120135) {
                        if (ch < 120134) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 120138) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120145) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 120780) {
                        if (ch < 120486) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120488) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 120782) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120832) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 126501) {
                    if (ch < 126468) {
                      if (ch < 125127) {
                        if (ch < 125125) {
                          counts[mende_kikakui] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 125143) {
                          counts[mende_kikakui] += 1;
                        } else {
                          if (ch < 126464) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126497) {
                        if (ch < 126469) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126496) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126499) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126500) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126516) {
                      if (ch < 126504) {
                        if (ch < 126503) {
                          counts[unknown] += 1;
                        } else {
                          counts[arabic] += 1;
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
                        if (ch < 126523) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126524) {
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
                if (ch < 126559) {
                  if (ch < 126547) {
                    if (ch < 126538) {
                      if (ch < 126535) {
                        if (ch < 126531) {
                          counts[arabic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 126536) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126537) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126541) {
                        if (ch < 126539) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126540) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126544) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126545) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126553) {
                      if (ch < 126549) {
                        if (ch < 126548) {
                          counts[unknown] += 1;
                        } else {
                          counts[arabic] += 1;
                        }
                      } else {
                        if (ch < 126551) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126552) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126556) {
                        if (ch < 126554) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126555) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126557) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126558) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 126584) {
                    if (ch < 126565) {
                      if (ch < 126561) {
                        if (ch < 126560) {
                          counts[arabic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 126563) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126564) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
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
                        if (ch < 126579) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126580) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126592) {
                      if (ch < 126589) {
                        if (ch < 126585) {
                          counts[unknown] += 1;
                        } else {
                          counts[arabic] += 1;
                        }
                      } else {
                        if (ch < 126590) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126591) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126620) {
                        if (ch < 126602) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126603) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126625) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126628) {
                            counts[arabic] += 1;
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
              if (ch < 128000) {
                if (ch < 127280) {
                  if (ch < 127151) {
                    if (ch < 126706) {
                      if (ch < 126635) {
                        if (ch < 126634) {
                          counts[arabic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 126652) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126704) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 127024) {
                        if (ch < 126976) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127020) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 127124) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127136) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 127185) {
                      if (ch < 127168) {
                        if (ch < 127153) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
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
                      if (ch < 127245) {
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
                        if (ch < 127248) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127279) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 127561) {
                    if (ch < 127488) {
                      if (ch < 127344) {
                        if (ch < 127340) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 127387) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127462) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 127504) {
                        if (ch < 127489) {
                          counts[hiragana] += 1;
                        } else {
                          if (ch < 127491) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 127547) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127552) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 127792) {
                      if (ch < 127570) {
                        if (ch < 127568) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 127744) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127789) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 127951) {
                        if (ch < 127870) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127872) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 127956) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127992) {
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
                if (ch < 129040) {
                  if (ch < 128720) {
                    if (ch < 128378) {
                      if (ch < 128256) {
                        if (ch < 128255) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 128331) {
                          counts[common] += 1;
                        } else {
                          if (ch < 128336) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 128421) {
                        if (ch < 128379) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 128420) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 128579) {
                          counts[common] += 1;
                        } else {
                          if (ch < 128581) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 128768) {
                      if (ch < 128749) {
                        if (ch < 128736) {
                          counts[unknown] += 1;
                        } else {
                          counts[common] += 1;
                        }
                      } else {
                        if (ch < 128752) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 128756) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 128981) {
                        if (ch < 128884) {
                          counts[common] += 1;
                        } else {
                          if (ch < 128896) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 129024) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129036) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 177973) {
                    if (ch < 129160) {
                      if (ch < 129104) {
                        if (ch < 129096) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 129114) {
                          counts[common] += 1;
                        } else {
                          if (ch < 129120) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 131072) {
                        if (ch < 129168) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129198) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 173783) {
                          counts[han] += 1;
                        } else {
                          if (ch < 173824) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 917505) {
                      if (ch < 178206) {
                        if (ch < 177984) {
                          counts[unknown] += 1;
                        } else {
                          counts[han] += 1;
                        }
                      } else {
                        if (ch < 194560) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 195102) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 917632) {
                        if (ch < 917506) {
                          counts[common] += 1;
                        } else {
                          if (ch < 917536) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 917760) {
                          counts[unknown] += 1;
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

  for (i = 0; i < 126; ++i) {
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
