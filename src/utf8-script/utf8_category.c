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
  {"long-names", 0, NULL, 'l'},
  {0, 0, 0, 0}
};

enum unicode_category {
  cc = 0,
  cf = 1,
  co = 2,
  cs = 3,
  ll = 4,
  lm = 5,
  lo = 6,
  lt = 7,
  lu = 8,
  mc = 9,
  me = 10,
  mn = 11,
  nd = 12,
  nl = 13,
  no = 14,
  pc = 15,
  pd = 16,
  pe = 17,
  pf = 18,
  pi = 19,
  po = 20,
  ps = 21,
  sc = 22,
  sk = 23,
  sm = 24,
  so = 25,
  unknown = 26,
  zl = 27,
  zp = 28,
  zs = 29,
};

char *categories[] = {
  "Cc",
  "Cf",
  "Co",
  "Cs",
  "Ll",
  "Lm",
  "Lo",
  "Lt",
  "Lu",
  "Mc",
  "Me",
  "Mn",
  "Nd",
  "Nl",
  "No",
  "Pc",
  "Pd",
  "Pe",
  "Pf",
  "Pi",
  "Po",
  "Ps",
  "Sc",
  "Sk",
  "Sm",
  "So",
  "Unknown",
  "Zl",
  "Zp",
  "Zs"
};

char *long_categories[] = {
  "Control",
  "Format",
  "Private_Use",
  "Surrogate",
  "Lowercase_Letter",
  "Modifier_Letter",
  "Other_Letter",
  "Titlecase_Letter",
  "Uppercase_Letter",
  "Spacing_Mark",
  "Enclosing_Mark",
  "Nonspacing_Mark",
  "Decimal_Number",
  "Letter_Number",
  "Other_Number",
  "Connector_Punctuation",
  "Dash_Punctuation",
  "Close_Punctuation",
  "Final_Punctuation",
  "Initial_Punctuation",
  "Other_Punctuation",
  "Open_Punctuation",
  "Currency_Symbol",
  "Modifier_Symbol",
  "Math_Symbol",
  "Other_Symbol",
  "Unknown",
  "Line_Separator",
  "Paragraph_Separator",
  "Space_Separator"
};

void
usage(int exit_status) {
  fprintf(stderr, "USAGE: utf8-category [-l|--long-names] [-c|--count-ascii|-s|--skip-ascii]\n");
  exit(exit_status);
}

int
main(int argc, char **argv) {
  wchar_t ch;
  size_t counts[30];
  int flag, flag_count = 0;
  char *endptr;
  bool count_ascii = false;
  size_t ascii_cnt = 0;
  bool skip_ascii = false;
  bool long_names = false;

  while (true) {
    flag = getopt_long(argc, argv, "cls", long_opts, NULL);
    if (-1 == flag)
      break;
    switch(flag) {
    case 'c':
      count_ascii = true;
      flag_count += 1;
      break;
    case 'l':
      long_names = true;
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
  for (i = 0; i < 30; ++i) {
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
      if (ch < 60) {
        if (ch < 42) {
          if (ch < 36) {
            if (ch < 32) {
              counts[cc] += 1;
            } else {
              if (ch < 33) {
                counts[zs] += 1;
              } else {
                counts[po] += 1;
              }
            }
          } else {
            if (ch < 40) {
              if (ch < 37) {
                counts[sc] += 1;
              } else {
                counts[po] += 1;
              }
            } else {
              if (ch < 41) {
                counts[ps] += 1;
              } else {
                counts[pe] += 1;
              }
            }
          }
        } else {
          if (ch < 45) {
            if (ch < 43) {
              counts[po] += 1;
            } else {
              if (ch < 44) {
                counts[sm] += 1;
              } else {
                counts[po] += 1;
              }
            }
          } else {
            if (ch < 48) {
              if (ch < 46) {
                counts[pd] += 1;
              } else {
                counts[po] += 1;
              }
            } else {
              if (ch < 58) {
                counts[nd] += 1;
              } else {
                counts[po] += 1;
              }
            }
          }
        }
      } else {
        if (ch < 95) {
          if (ch < 91) {
            if (ch < 63) {
              counts[sm] += 1;
            } else {
              if (ch < 65) {
                counts[po] += 1;
              } else {
                counts[lu] += 1;
              }
            }
          } else {
            if (ch < 93) {
              if (ch < 92) {
                counts[ps] += 1;
              } else {
                counts[po] += 1;
              }
            } else {
              if (ch < 94) {
                counts[pe] += 1;
              } else {
                counts[sk] += 1;
              }
            }
          }
        } else {
          if (ch < 124) {
            if (ch < 97) {
              if (ch < 96) {
                counts[pc] += 1;
              } else {
                counts[sk] += 1;
              }
            } else {
              if (ch < 123) {
                counts[ll] += 1;
              } else {
                counts[ps] += 1;
              }
            }
          } else {
            if (ch < 126) {
              if (ch < 125) {
                counts[sm] += 1;
              } else {
                counts[pe] += 1;
              }
            } else {
              if (ch < 127) {
                counts[sm] += 1;
              } else {
                counts[cc] += 1;
              }
            }
          }
        }
      }
    } else {
      if (ch < 7895) {
        if (ch < 1786) {
          if (ch < 660) {
            if (ch < 390) {
              if (ch < 304) {
                if (ch < 264) {
                  if (ch < 184) {
                    if (ch < 172) {
                      if (ch < 167) {
                        if (ch < 161) {
                          if (ch < 160) {
                            counts[cc] += 1;
                          } else {
                            counts[zs] += 1;
                          }
                        } else {
                          if (ch < 162) {
                            counts[po] += 1;
                          } else {
                            if (ch < 166) {
                              counts[sc] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 169) {
                          if (ch < 168) {
                            counts[po] += 1;
                          } else {
                            counts[sk] += 1;
                          }
                        } else {
                          if (ch < 170) {
                            counts[so] += 1;
                          } else {
                            if (ch < 171) {
                              counts[lo] += 1;
                            } else {
                              counts[pi] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 177) {
                        if (ch < 174) {
                          if (ch < 173) {
                            counts[sm] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 175) {
                            counts[so] += 1;
                          } else {
                            if (ch < 176) {
                              counts[sk] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 180) {
                          if (ch < 178) {
                            counts[sm] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 181) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 182) {
                              counts[ll] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 247) {
                      if (ch < 191) {
                        if (ch < 186) {
                          if (ch < 185) {
                            counts[sk] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 187) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 188) {
                              counts[pf] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 215) {
                          if (ch < 192) {
                            counts[po] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 216) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 223) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 259) {
                        if (ch < 256) {
                          if (ch < 248) {
                            counts[sm] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 257) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 258) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 261) {
                          if (ch < 260) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 262) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 263) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 284) {
                    if (ch < 274) {
                      if (ch < 269) {
                        if (ch < 266) {
                          if (ch < 265) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 267) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 268) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 271) {
                          if (ch < 270) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 272) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 273) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 279) {
                        if (ch < 276) {
                          if (ch < 275) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 277) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 278) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 281) {
                          if (ch < 280) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 282) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 283) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 294) {
                      if (ch < 289) {
                        if (ch < 286) {
                          if (ch < 285) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 287) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 288) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 291) {
                          if (ch < 290) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 292) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 293) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 299) {
                        if (ch < 296) {
                          if (ch < 295) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 297) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 298) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 301) {
                          if (ch < 300) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 302) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 303) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 346) {
                  if (ch < 325) {
                    if (ch < 315) {
                      if (ch < 309) {
                        if (ch < 306) {
                          if (ch < 305) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 307) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 308) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 311) {
                          if (ch < 310) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 313) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 314) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 320) {
                        if (ch < 317) {
                          if (ch < 316) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 318) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 319) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 322) {
                          if (ch < 321) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 323) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 324) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 336) {
                      if (ch < 331) {
                        if (ch < 327) {
                          if (ch < 326) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 328) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 330) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 333) {
                          if (ch < 332) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 334) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 335) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 341) {
                        if (ch < 338) {
                          if (ch < 337) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 339) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 340) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 343) {
                          if (ch < 342) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 344) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 345) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 366) {
                    if (ch < 356) {
                      if (ch < 351) {
                        if (ch < 348) {
                          if (ch < 347) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 349) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 350) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 353) {
                          if (ch < 352) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 354) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 355) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 361) {
                        if (ch < 358) {
                          if (ch < 357) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 359) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 360) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 363) {
                          if (ch < 362) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 364) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 365) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 376) {
                      if (ch < 371) {
                        if (ch < 368) {
                          if (ch < 367) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 369) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 370) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 373) {
                          if (ch < 372) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 374) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 375) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 382) {
                        if (ch < 379) {
                          if (ch < 378) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 380) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 381) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 387) {
                          if (ch < 385) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 388) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 389) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 498) {
                if (ch < 456) {
                  if (ch < 425) {
                    if (ch < 412) {
                      if (ch < 402) {
                        if (ch < 393) {
                          if (ch < 392) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 396) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 398) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 405) {
                          if (ch < 403) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 406) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 409) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 419) {
                        if (ch < 415) {
                          if (ch < 414) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 417) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 418) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 421) {
                          if (ch < 420) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 422) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 424) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 439) {
                      if (ch < 432) {
                        if (ch < 428) {
                          if (ch < 426) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 429) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 430) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 436) {
                          if (ch < 433) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 437) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 438) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 448) {
                        if (ch < 443) {
                          if (ch < 441) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 444) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 445) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 453) {
                          if (ch < 452) {
                            counts[lo] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 454) {
                            counts[lt] += 1;
                          } else {
                            if (ch < 455) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 476) {
                    if (ch < 466) {
                      if (ch < 461) {
                        if (ch < 458) {
                          if (ch < 457) {
                            counts[lt] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 459) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 460) {
                              counts[lt] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 463) {
                          if (ch < 462) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 464) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 465) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 471) {
                        if (ch < 468) {
                          if (ch < 467) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 469) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 470) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 473) {
                          if (ch < 472) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 474) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 475) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 487) {
                      if (ch < 482) {
                        if (ch < 479) {
                          if (ch < 478) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 480) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 481) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 484) {
                          if (ch < 483) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 485) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 486) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 492) {
                        if (ch < 489) {
                          if (ch < 488) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 490) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 491) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 494) {
                          if (ch < 493) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 495) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 497) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 540) {
                  if (ch < 520) {
                    if (ch < 510) {
                      if (ch < 505) {
                        if (ch < 500) {
                          if (ch < 499) {
                            counts[lt] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 501) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 502) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 507) {
                          if (ch < 506) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 508) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 509) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 515) {
                        if (ch < 512) {
                          if (ch < 511) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 513) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 514) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 517) {
                          if (ch < 516) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 518) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 519) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 530) {
                      if (ch < 525) {
                        if (ch < 522) {
                          if (ch < 521) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 523) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 524) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 527) {
                          if (ch < 526) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 528) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 529) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 535) {
                        if (ch < 532) {
                          if (ch < 531) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 533) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 534) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 537) {
                          if (ch < 536) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 538) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 539) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 560) {
                    if (ch < 550) {
                      if (ch < 545) {
                        if (ch < 542) {
                          if (ch < 541) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 543) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 544) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 547) {
                          if (ch < 546) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 548) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 549) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 555) {
                        if (ch < 552) {
                          if (ch < 551) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 553) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 554) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 557) {
                          if (ch < 556) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 558) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 559) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 579) {
                      if (ch < 572) {
                        if (ch < 562) {
                          if (ch < 561) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 563) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 570) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 575) {
                          if (ch < 573) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 577) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 578) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 587) {
                        if (ch < 584) {
                          if (ch < 583) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 585) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 586) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 589) {
                          if (ch < 588) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 590) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 591) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
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
            if (ch < 1216) {
              if (ch < 1131) {
                if (ch < 988) {
                  if (ch < 887) {
                    if (ch < 750) {
                      if (ch < 722) {
                        if (ch < 688) {
                          if (ch < 661) {
                            counts[lo] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 706) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 710) {
                              counts[sk] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 741) {
                          if (ch < 736) {
                            counts[sk] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 748) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 749) {
                              counts[lm] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 882) {
                        if (ch < 768) {
                          if (ch < 751) {
                            counts[lm] += 1;
                          } else {
                            counts[sk] += 1;
                          }
                        } else {
                          if (ch < 880) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 881) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 884) {
                          if (ch < 883) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 885) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 886) {
                              counts[sk] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 913) {
                      if (ch < 900) {
                        if (ch < 891) {
                          if (ch < 890) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 894) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 895) {
                              counts[po] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 903) {
                          if (ch < 902) {
                            counts[sk] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 904) {
                            counts[po] += 1;
                          } else {
                            if (ch < 912) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 981) {
                        if (ch < 975) {
                          if (ch < 940) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 976) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 978) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 985) {
                          if (ch < 984) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 986) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 987) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 1012) {
                    if (ch < 998) {
                      if (ch < 993) {
                        if (ch < 990) {
                          if (ch < 989) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 991) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 992) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 995) {
                          if (ch < 994) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 996) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 997) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1003) {
                        if (ch < 1000) {
                          if (ch < 999) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1001) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1002) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1005) {
                          if (ch < 1004) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1006) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1007) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1121) {
                      if (ch < 1017) {
                        if (ch < 1014) {
                          if (ch < 1013) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1015) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 1016) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1021) {
                          if (ch < 1019) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1072) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1120) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1126) {
                        if (ch < 1123) {
                          if (ch < 1122) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1124) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1125) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1128) {
                          if (ch < 1127) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1129) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1130) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 1176) {
                  if (ch < 1151) {
                    if (ch < 1141) {
                      if (ch < 1136) {
                        if (ch < 1133) {
                          if (ch < 1132) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1134) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1135) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1138) {
                          if (ch < 1137) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1139) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1140) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1146) {
                        if (ch < 1143) {
                          if (ch < 1142) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1144) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1145) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1148) {
                          if (ch < 1147) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1149) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1150) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1166) {
                      if (ch < 1160) {
                        if (ch < 1153) {
                          if (ch < 1152) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1154) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1155) {
                              counts[so] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1163) {
                          if (ch < 1162) {
                            counts[me] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1164) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1165) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1171) {
                        if (ch < 1168) {
                          if (ch < 1167) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1169) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1170) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1173) {
                          if (ch < 1172) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1174) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1175) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 1196) {
                    if (ch < 1186) {
                      if (ch < 1181) {
                        if (ch < 1178) {
                          if (ch < 1177) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1179) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1180) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1183) {
                          if (ch < 1182) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1184) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1185) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1191) {
                        if (ch < 1188) {
                          if (ch < 1187) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1189) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1190) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1193) {
                          if (ch < 1192) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1194) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1195) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1206) {
                      if (ch < 1201) {
                        if (ch < 1198) {
                          if (ch < 1197) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1199) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1200) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1203) {
                          if (ch < 1202) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1204) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1205) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1211) {
                        if (ch < 1208) {
                          if (ch < 1207) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1209) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1210) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1213) {
                          if (ch < 1212) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1214) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1215) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 1298) {
                if (ch < 1258) {
                  if (ch < 1238) {
                    if (ch < 1227) {
                      if (ch < 1222) {
                        if (ch < 1219) {
                          if (ch < 1218) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1220) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1221) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1224) {
                          if (ch < 1223) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1225) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1226) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1233) {
                        if (ch < 1229) {
                          if (ch < 1228) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1230) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1232) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1235) {
                          if (ch < 1234) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1236) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1237) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1248) {
                      if (ch < 1243) {
                        if (ch < 1240) {
                          if (ch < 1239) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1241) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1242) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1245) {
                          if (ch < 1244) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1246) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1247) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1253) {
                        if (ch < 1250) {
                          if (ch < 1249) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1251) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1252) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1255) {
                          if (ch < 1254) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1256) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1257) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 1278) {
                    if (ch < 1268) {
                      if (ch < 1263) {
                        if (ch < 1260) {
                          if (ch < 1259) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1261) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1262) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1265) {
                          if (ch < 1264) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1266) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1267) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1273) {
                        if (ch < 1270) {
                          if (ch < 1269) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1271) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1272) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1275) {
                          if (ch < 1274) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1276) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1277) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1288) {
                      if (ch < 1283) {
                        if (ch < 1280) {
                          if (ch < 1279) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1281) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1282) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1285) {
                          if (ch < 1284) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1286) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1287) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1293) {
                        if (ch < 1290) {
                          if (ch < 1289) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1291) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1292) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1295) {
                          if (ch < 1294) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1296) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1297) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 1471) {
                  if (ch < 1318) {
                    if (ch < 1308) {
                      if (ch < 1303) {
                        if (ch < 1300) {
                          if (ch < 1299) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1301) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1302) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1305) {
                          if (ch < 1304) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1306) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1307) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1313) {
                        if (ch < 1310) {
                          if (ch < 1309) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1311) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1312) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1315) {
                          if (ch < 1314) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1316) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1317) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1329) {
                      if (ch < 1323) {
                        if (ch < 1320) {
                          if (ch < 1319) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1321) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1322) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1325) {
                          if (ch < 1324) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1326) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1327) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1418) {
                        if (ch < 1370) {
                          if (ch < 1369) {
                            counts[lu] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 1377) {
                            counts[po] += 1;
                          } else {
                            if (ch < 1417) {
                              counts[ll] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1423) {
                          if (ch < 1421) {
                            counts[pd] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 1425) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 1470) {
                              counts[mn] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 1600) {
                    if (ch < 1542) {
                      if (ch < 1478) {
                        if (ch < 1473) {
                          if (ch < 1472) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 1475) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1476) {
                              counts[po] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1488) {
                          if (ch < 1479) {
                            counts[po] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 1523) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1536) {
                              counts[po] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1552) {
                        if (ch < 1547) {
                          if (ch < 1545) {
                            counts[sm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 1548) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 1550) {
                              counts[po] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1564) {
                          if (ch < 1563) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 1566) {
                            counts[cf] += 1;
                          } else {
                            if (ch < 1568) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1750) {
                      if (ch < 1646) {
                        if (ch < 1611) {
                          if (ch < 1601) {
                            counts[lm] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 1632) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1642) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1649) {
                          if (ch < 1648) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 1748) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1749) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1767) {
                        if (ch < 1758) {
                          if (ch < 1757) {
                            counts[mn] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 1759) {
                            counts[so] += 1;
                          } else {
                            if (ch < 1765) {
                              counts[mn] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1770) {
                          if (ch < 1769) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 1774) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1776) {
                              counts[lo] += 1;
                            } else {
                              counts[nd] += 1;
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
          if (ch < 6176) {
            if (ch < 3405) {
              if (ch < 2672) {
                if (ch < 2369) {
                  if (ch < 2070) {
                    if (ch < 1958) {
                      if (ch < 1808) {
                        if (ch < 1791) {
                          if (ch < 1789) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 1792) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1807) {
                              counts[po] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1810) {
                          if (ch < 1809) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 1840) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1869) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2036) {
                        if (ch < 1984) {
                          if (ch < 1969) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 1994) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 2027) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2039) {
                          if (ch < 2038) {
                            counts[lm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 2042) {
                            counts[po] += 1;
                          } else {
                            if (ch < 2048) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2142) {
                      if (ch < 2088) {
                        if (ch < 2075) {
                          if (ch < 2074) {
                            counts[mn] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 2084) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2085) {
                              counts[lm] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2096) {
                          if (ch < 2089) {
                            counts[lm] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2112) {
                            counts[po] += 1;
                          } else {
                            if (ch < 2137) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2362) {
                        if (ch < 2276) {
                          if (ch < 2208) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2307) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2308) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2364) {
                          if (ch < 2363) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 2365) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2366) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2503) {
                    if (ch < 2416) {
                      if (ch < 2385) {
                        if (ch < 2381) {
                          if (ch < 2377) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 2382) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2384) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2402) {
                          if (ch < 2392) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2404) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2406) {
                              counts[po] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2437) {
                        if (ch < 2418) {
                          if (ch < 2417) {
                            counts[po] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 2433) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2434) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2493) {
                          if (ch < 2492) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2494) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2497) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2554) {
                      if (ch < 2530) {
                        if (ch < 2510) {
                          if (ch < 2509) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2519) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2524) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2544) {
                          if (ch < 2534) {
                            counts[mn] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 2546) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2548) {
                              counts[sc] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2620) {
                        if (ch < 2561) {
                          if (ch < 2555) {
                            counts[so] += 1;
                          } else {
                            counts[sc] += 1;
                          }
                        } else {
                          if (ch < 2563) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2565) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2625) {
                          if (ch < 2622) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 2649) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2662) {
                              counts[lo] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 3024) {
                  if (ch < 2877) {
                    if (ch < 2765) {
                      if (ch < 2748) {
                        if (ch < 2677) {
                          if (ch < 2674) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2691) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2693) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2750) {
                          if (ch < 2749) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2753) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2761) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2801) {
                        if (ch < 2786) {
                          if (ch < 2768) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2790) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2800) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2818) {
                          if (ch < 2817) {
                            counts[sc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2821) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2876) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2918) {
                      if (ch < 2887) {
                        if (ch < 2879) {
                          if (ch < 2878) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 2880) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2881) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2903) {
                          if (ch < 2893) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2908) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2914) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2947) {
                        if (ch < 2929) {
                          if (ch < 2928) {
                            counts[nd] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 2930) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2946) {
                              counts[no] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3008) {
                          if (ch < 3006) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 3009) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3021) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3205) {
                    if (ch < 3134) {
                      if (ch < 3065) {
                        if (ch < 3046) {
                          if (ch < 3031) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 3056) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 3059) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3072) {
                          if (ch < 3066) {
                            counts[sc] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 3073) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3077) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3174) {
                        if (ch < 3142) {
                          if (ch < 3137) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 3160) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3170) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3199) {
                          if (ch < 3192) {
                            counts[nd] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 3201) {
                            counts[so] += 1;
                          } else {
                            if (ch < 3202) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3294) {
                      if (ch < 3264) {
                        if (ch < 3261) {
                          if (ch < 3260) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3262) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3263) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3271) {
                          if (ch < 3270) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3276) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3285) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3330) {
                        if (ch < 3302) {
                          if (ch < 3298) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3313) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 3329) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3390) {
                          if (ch < 3333) {
                            counts[mc] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 3393) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3398) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 4157) {
                if (ch < 3859) {
                  if (ch < 3634) {
                    if (ch < 3461) {
                      if (ch < 3430) {
                        if (ch < 3415) {
                          if (ch < 3406) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 3424) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3426) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3449) {
                          if (ch < 3440) {
                            counts[nd] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 3450) {
                            counts[so] += 1;
                          } else {
                            if (ch < 3458) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3558) {
                        if (ch < 3535) {
                          if (ch < 3530) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3538) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3544) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3572) {
                          if (ch < 3570) {
                            counts[nd] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 3585) {
                            counts[po] += 1;
                          } else {
                            if (ch < 3633) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3761) {
                      if (ch < 3655) {
                        if (ch < 3647) {
                          if (ch < 3636) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3648) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 3654) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3664) {
                          if (ch < 3663) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 3674) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 3713) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3784) {
                        if (ch < 3764) {
                          if (ch < 3762) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 3773) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3782) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3804) {
                          if (ch < 3792) {
                            counts[mn] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 3841) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3844) {
                              counts[so] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3967) {
                    if (ch < 3895) {
                      if (ch < 3872) {
                        if (ch < 3861) {
                          if (ch < 3860) {
                            counts[so] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 3864) {
                            counts[so] += 1;
                          } else {
                            if (ch < 3866) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3892) {
                          if (ch < 3882) {
                            counts[nd] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 3893) {
                            counts[so] += 1;
                          } else {
                            if (ch < 3894) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3900) {
                        if (ch < 3897) {
                          if (ch < 3896) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 3898) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3899) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3902) {
                          if (ch < 3901) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 3904) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3953) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4053) {
                      if (ch < 3981) {
                        if (ch < 3973) {
                          if (ch < 3968) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3974) {
                            counts[po] += 1;
                          } else {
                            if (ch < 3976) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4038) {
                          if (ch < 4030) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 4039) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 4048) {
                              counts[so] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4145) {
                        if (ch < 4096) {
                          if (ch < 4057) {
                            counts[so] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 4139) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 4141) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4152) {
                          if (ch < 4146) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 4153) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4155) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 5741) {
                  if (ch < 4237) {
                    if (ch < 4194) {
                      if (ch < 4182) {
                        if (ch < 4160) {
                          if (ch < 4159) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 4170) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 4176) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4186) {
                          if (ch < 4184) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 4190) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 4193) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4213) {
                        if (ch < 4199) {
                          if (ch < 4197) {
                            counts[mc] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 4206) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4209) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4227) {
                          if (ch < 4226) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 4229) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4231) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4348) {
                      if (ch < 4253) {
                        if (ch < 4239) {
                          if (ch < 4238) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 4240) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4250) {
                              counts[nd] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4256) {
                          if (ch < 4254) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 4304) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 4347) {
                              counts[lo] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4992) {
                        if (ch < 4957) {
                          if (ch < 4349) {
                            counts[lm] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 4960) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 4969) {
                              counts[po] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 5024) {
                          if (ch < 5008) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 5120) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 5121) {
                              counts[pd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 6070) {
                    if (ch < 5906) {
                      if (ch < 5788) {
                        if (ch < 5760) {
                          if (ch < 5743) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 5761) {
                            counts[zs] += 1;
                          } else {
                            if (ch < 5787) {
                              counts[lo] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 5867) {
                          if (ch < 5792) {
                            counts[pe] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 5870) {
                            counts[po] += 1;
                          } else {
                            if (ch < 5873) {
                              counts[nl] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 5970) {
                        if (ch < 5938) {
                          if (ch < 5920) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 5941) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 5952) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6002) {
                          if (ch < 5984) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 6016) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6068) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6108) {
                      if (ch < 6089) {
                        if (ch < 6078) {
                          if (ch < 6071) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6086) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6087) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6103) {
                          if (ch < 6100) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 6104) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 6107) {
                              counts[po] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6150) {
                        if (ch < 6112) {
                          if (ch < 6109) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6128) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 6144) {
                              counts[no] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6155) {
                          if (ch < 6151) {
                            counts[pd] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 6158) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6160) {
                              counts[cf] += 1;
                            } else {
                              counts[nd] += 1;
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
            if (ch < 7727) {
              if (ch < 7154) {
                if (ch < 6823) {
                  if (ch < 6618) {
                    if (ch < 6451) {
                      if (ch < 6432) {
                        if (ch < 6212) {
                          if (ch < 6211) {
                            counts[lo] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 6313) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6314) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6439) {
                          if (ch < 6435) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 6441) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6450) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6480) {
                        if (ch < 6464) {
                          if (ch < 6457) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6468) {
                            counts[so] += 1;
                          } else {
                            if (ch < 6470) {
                              counts[po] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6593) {
                          if (ch < 6576) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 6600) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6608) {
                              counts[mc] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6743) {
                      if (ch < 6683) {
                        if (ch < 6656) {
                          if (ch < 6622) {
                            counts[no] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 6679) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6681) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6688) {
                          if (ch < 6686) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 6741) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6742) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6757) {
                        if (ch < 6753) {
                          if (ch < 6744) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6754) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6755) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6771) {
                          if (ch < 6765) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 6784) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6816) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 7028) {
                    if (ch < 6971) {
                      if (ch < 6916) {
                        if (ch < 6832) {
                          if (ch < 6824) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 6846) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6912) {
                              counts[me] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6964) {
                          if (ch < 6917) {
                            counts[mc] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 6965) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6966) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6981) {
                        if (ch < 6973) {
                          if (ch < 6972) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6978) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6979) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7002) {
                          if (ch < 6992) {
                            counts[lo] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 7009) {
                            counts[po] += 1;
                          } else {
                            if (ch < 7019) {
                              counts[so] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7086) {
                      if (ch < 7074) {
                        if (ch < 7042) {
                          if (ch < 7040) {
                            counts[so] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 7043) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 7073) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7080) {
                          if (ch < 7078) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 7082) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 7083) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7144) {
                        if (ch < 7098) {
                          if (ch < 7088) {
                            counts[lo] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 7142) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 7143) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7149) {
                          if (ch < 7146) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 7150) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 7151) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 7687) {
                  if (ch < 7405) {
                    if (ch < 7248) {
                      if (ch < 7220) {
                        if (ch < 7168) {
                          if (ch < 7164) {
                            counts[mc] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 7204) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 7212) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7227) {
                          if (ch < 7222) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 7232) {
                            counts[po] += 1;
                          } else {
                            if (ch < 7245) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7379) {
                        if (ch < 7288) {
                          if (ch < 7258) {
                            counts[nd] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 7294) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 7376) {
                              counts[po] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7393) {
                          if (ch < 7380) {
                            counts[po] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 7394) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 7401) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7545) {
                      if (ch < 7416) {
                        if (ch < 7410) {
                          if (ch < 7406) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 7412) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 7413) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7468) {
                          if (ch < 7424) {
                            counts[mn] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7531) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 7544) {
                              counts[ll] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7682) {
                        if (ch < 7616) {
                          if (ch < 7579) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 7680) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 7681) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7684) {
                          if (ch < 7683) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7685) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7686) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 7707) {
                    if (ch < 7697) {
                      if (ch < 7692) {
                        if (ch < 7689) {
                          if (ch < 7688) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7690) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7691) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7694) {
                          if (ch < 7693) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7695) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7696) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7702) {
                        if (ch < 7699) {
                          if (ch < 7698) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7700) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7701) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7704) {
                          if (ch < 7703) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7705) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7706) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7717) {
                      if (ch < 7712) {
                        if (ch < 7709) {
                          if (ch < 7708) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7710) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7711) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7714) {
                          if (ch < 7713) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7715) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7716) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7722) {
                        if (ch < 7719) {
                          if (ch < 7718) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7720) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7721) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7724) {
                          if (ch < 7723) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7725) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7726) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 7807) {
                if (ch < 7767) {
                  if (ch < 7747) {
                    if (ch < 7737) {
                      if (ch < 7732) {
                        if (ch < 7729) {
                          if (ch < 7728) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7730) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7731) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7734) {
                          if (ch < 7733) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7735) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7736) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7742) {
                        if (ch < 7739) {
                          if (ch < 7738) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7740) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7741) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7744) {
                          if (ch < 7743) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7745) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7746) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7757) {
                      if (ch < 7752) {
                        if (ch < 7749) {
                          if (ch < 7748) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7750) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7751) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7754) {
                          if (ch < 7753) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7755) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7756) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7762) {
                        if (ch < 7759) {
                          if (ch < 7758) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7760) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7761) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7764) {
                          if (ch < 7763) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7765) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7766) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 7787) {
                    if (ch < 7777) {
                      if (ch < 7772) {
                        if (ch < 7769) {
                          if (ch < 7768) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7770) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7771) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7774) {
                          if (ch < 7773) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7775) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7776) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7782) {
                        if (ch < 7779) {
                          if (ch < 7778) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7780) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7781) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7784) {
                          if (ch < 7783) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7785) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7786) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7797) {
                      if (ch < 7792) {
                        if (ch < 7789) {
                          if (ch < 7788) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7790) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7791) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7794) {
                          if (ch < 7793) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7795) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7796) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7802) {
                        if (ch < 7799) {
                          if (ch < 7798) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7800) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7801) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7804) {
                          if (ch < 7803) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7805) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7806) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 7855) {
                  if (ch < 7827) {
                    if (ch < 7817) {
                      if (ch < 7812) {
                        if (ch < 7809) {
                          if (ch < 7808) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7810) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7811) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7814) {
                          if (ch < 7813) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7815) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7816) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7822) {
                        if (ch < 7819) {
                          if (ch < 7818) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7820) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7821) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7824) {
                          if (ch < 7823) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7825) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7826) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7845) {
                      if (ch < 7840) {
                        if (ch < 7829) {
                          if (ch < 7828) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7838) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7839) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7842) {
                          if (ch < 7841) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7843) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7844) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7850) {
                        if (ch < 7847) {
                          if (ch < 7846) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7848) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7849) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7852) {
                          if (ch < 7851) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7853) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7854) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 7875) {
                    if (ch < 7865) {
                      if (ch < 7860) {
                        if (ch < 7857) {
                          if (ch < 7856) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7858) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7859) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7862) {
                          if (ch < 7861) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7863) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7864) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7870) {
                        if (ch < 7867) {
                          if (ch < 7866) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7868) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7869) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7872) {
                          if (ch < 7871) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7873) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7874) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7885) {
                      if (ch < 7880) {
                        if (ch < 7877) {
                          if (ch < 7876) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7878) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7879) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7882) {
                          if (ch < 7881) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7883) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7884) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7890) {
                        if (ch < 7887) {
                          if (ch < 7886) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7888) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7889) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7892) {
                          if (ch < 7891) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7893) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7894) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
      } else {
        if (ch < 42786) {
          if (ch < 11400) {
            if (ch < 8508) {
              if (ch < 8192) {
                if (ch < 7935) {
                  if (ch < 7915) {
                    if (ch < 7905) {
                      if (ch < 7900) {
                        if (ch < 7897) {
                          if (ch < 7896) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7898) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7899) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7902) {
                          if (ch < 7901) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7903) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7904) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7910) {
                        if (ch < 7907) {
                          if (ch < 7906) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7908) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7909) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7912) {
                          if (ch < 7911) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7913) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7914) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7925) {
                      if (ch < 7920) {
                        if (ch < 7917) {
                          if (ch < 7916) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7918) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7919) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7922) {
                          if (ch < 7921) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7923) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7924) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7930) {
                        if (ch < 7927) {
                          if (ch < 7926) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7928) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7929) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7932) {
                          if (ch < 7931) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7933) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7934) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 8112) {
                    if (ch < 8016) {
                      if (ch < 7976) {
                        if (ch < 7952) {
                          if (ch < 7944) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7960) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7968) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7992) {
                          if (ch < 7984) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8000) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8008) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8072) {
                        if (ch < 8032) {
                          if (ch < 8025) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8040) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8048) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8088) {
                          if (ch < 8080) {
                            counts[lt] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8096) {
                            counts[lt] += 1;
                          } else {
                            if (ch < 8104) {
                              counts[ll] += 1;
                            } else {
                              counts[lt] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8144) {
                      if (ch < 8127) {
                        if (ch < 8124) {
                          if (ch < 8120) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8125) {
                            counts[lt] += 1;
                          } else {
                            if (ch < 8126) {
                              counts[sk] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8136) {
                          if (ch < 8130) {
                            counts[sk] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8140) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8141) {
                              counts[lt] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8173) {
                        if (ch < 8157) {
                          if (ch < 8152) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8160) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 8168) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8184) {
                          if (ch < 8178) {
                            counts[sk] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8188) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8189) {
                              counts[lt] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 8330) {
                  if (ch < 8255) {
                    if (ch < 8223) {
                      if (ch < 8217) {
                        if (ch < 8208) {
                          if (ch < 8203) {
                            counts[zs] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 8214) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 8216) {
                              counts[po] += 1;
                            } else {
                              counts[pi] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8219) {
                          if (ch < 8218) {
                            counts[pf] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 8221) {
                            counts[pi] += 1;
                          } else {
                            if (ch < 8222) {
                              counts[pf] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8239) {
                        if (ch < 8232) {
                          if (ch < 8224) {
                            counts[pi] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 8233) {
                            counts[zl] += 1;
                          } else {
                            if (ch < 8234) {
                              counts[zp] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8249) {
                          if (ch < 8240) {
                            counts[zs] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 8250) {
                            counts[pi] += 1;
                          } else {
                            if (ch < 8251) {
                              counts[pf] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8287) {
                      if (ch < 8263) {
                        if (ch < 8260) {
                          if (ch < 8257) {
                            counts[pc] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 8261) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8262) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8275) {
                          if (ch < 8274) {
                            counts[po] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 8276) {
                            counts[po] += 1;
                          } else {
                            if (ch < 8277) {
                              counts[pc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8314) {
                        if (ch < 8304) {
                          if (ch < 8288) {
                            counts[zs] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 8305) {
                            counts[no] += 1;
                          } else {
                            if (ch < 8308) {
                              counts[lm] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8318) {
                          if (ch < 8317) {
                            counts[sm] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 8319) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 8320) {
                              counts[lm] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 8468) {
                    if (ch < 8448) {
                      if (ch < 8400) {
                        if (ch < 8334) {
                          if (ch < 8333) {
                            counts[sm] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 8336) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 8352) {
                              counts[lm] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8417) {
                          if (ch < 8413) {
                            counts[mn] += 1;
                          } else {
                            counts[me] += 1;
                          }
                        } else {
                          if (ch < 8418) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 8421) {
                              counts[me] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8458) {
                        if (ch < 8451) {
                          if (ch < 8450) {
                            counts[so] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8455) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8456) {
                              counts[lu] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8462) {
                          if (ch < 8459) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8464) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8467) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8488) {
                      if (ch < 8478) {
                        if (ch < 8470) {
                          if (ch < 8469) {
                            counts[so] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8472) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8473) {
                              counts[sm] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8485) {
                          if (ch < 8484) {
                            counts[so] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8486) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8487) {
                              counts[lu] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8496) {
                        if (ch < 8490) {
                          if (ch < 8489) {
                            counts[lu] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 8494) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8495) {
                              counts[so] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8501) {
                          if (ch < 8500) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8505) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 8506) {
                              counts[ll] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 10176) {
                if (ch < 8972) {
                  if (ch < 8608) {
                    if (ch < 8528) {
                      if (ch < 8522) {
                        if (ch < 8512) {
                          if (ch < 8510) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8517) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8518) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8524) {
                          if (ch < 8523) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 8526) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8527) {
                              counts[ll] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8585) {
                        if (ch < 8579) {
                          if (ch < 8544) {
                            counts[no] += 1;
                          } else {
                            counts[nl] += 1;
                          }
                        } else {
                          if (ch < 8580) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8581) {
                              counts[ll] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8597) {
                          if (ch < 8592) {
                            counts[no] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 8602) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8604) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8658) {
                      if (ch < 8615) {
                        if (ch < 8611) {
                          if (ch < 8609) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 8612) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8614) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8623) {
                          if (ch < 8622) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 8654) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8656) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8960) {
                        if (ch < 8660) {
                          if (ch < 8659) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 8661) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8692) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8969) {
                          if (ch < 8968) {
                            counts[so] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 8970) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 8971) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 9720) {
                    if (ch < 9180) {
                      if (ch < 9003) {
                        if (ch < 8994) {
                          if (ch < 8992) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 9001) {
                            counts[so] += 1;
                          } else {
                            if (ch < 9002) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 9085) {
                          if (ch < 9084) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 9115) {
                            counts[so] += 1;
                          } else {
                            if (ch < 9140) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 9472) {
                        if (ch < 9312) {
                          if (ch < 9186) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 9372) {
                            counts[no] += 1;
                          } else {
                            if (ch < 9450) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 9656) {
                          if (ch < 9655) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 9665) {
                            counts[so] += 1;
                          } else {
                            if (ch < 9666) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 10094) {
                      if (ch < 10089) {
                        if (ch < 9839) {
                          if (ch < 9728) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 9840) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 10088) {
                              counts[so] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10091) {
                          if (ch < 10090) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10092) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10093) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10099) {
                        if (ch < 10096) {
                          if (ch < 10095) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10097) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10098) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10101) {
                          if (ch < 10100) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10102) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10132) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 10712) {
                  if (ch < 10630) {
                    if (ch < 10220) {
                      if (ch < 10215) {
                        if (ch < 10182) {
                          if (ch < 10181) {
                            counts[sm] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10183) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10214) {
                              counts[sm] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10217) {
                          if (ch < 10216) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10218) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10219) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10240) {
                        if (ch < 10222) {
                          if (ch < 10221) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10223) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10224) {
                              counts[pe] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10627) {
                          if (ch < 10496) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 10628) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10629) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 10640) {
                      if (ch < 10635) {
                        if (ch < 10632) {
                          if (ch < 10631) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10633) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10634) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10637) {
                          if (ch < 10636) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10638) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10639) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10645) {
                        if (ch < 10642) {
                          if (ch < 10641) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10643) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10644) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10647) {
                          if (ch < 10646) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10648) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10649) {
                              counts[pe] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11368) {
                    if (ch < 11077) {
                      if (ch < 10748) {
                        if (ch < 10714) {
                          if (ch < 10713) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10715) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10716) {
                              counts[pe] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10750) {
                          if (ch < 10749) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 11008) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 11056) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11360) {
                        if (ch < 11085) {
                          if (ch < 11079) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 11264) {
                            counts[so] += 1;
                          } else {
                            if (ch < 11312) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11362) {
                          if (ch < 11361) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11365) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11367) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11382) {
                      if (ch < 11373) {
                        if (ch < 11370) {
                          if (ch < 11369) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11371) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11372) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11378) {
                          if (ch < 11377) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11379) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11381) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11395) {
                        if (ch < 11390) {
                          if (ch < 11388) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 11393) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11394) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11397) {
                          if (ch < 11396) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11398) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11399) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
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
            if (ch < 12302) {
              if (ch < 11480) {
                if (ch < 11440) {
                  if (ch < 11420) {
                    if (ch < 11410) {
                      if (ch < 11405) {
                        if (ch < 11402) {
                          if (ch < 11401) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11403) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11404) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11407) {
                          if (ch < 11406) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11408) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11409) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11415) {
                        if (ch < 11412) {
                          if (ch < 11411) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11413) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11414) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11417) {
                          if (ch < 11416) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11418) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11419) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11430) {
                      if (ch < 11425) {
                        if (ch < 11422) {
                          if (ch < 11421) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11423) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11424) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11427) {
                          if (ch < 11426) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11428) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11429) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11435) {
                        if (ch < 11432) {
                          if (ch < 11431) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11433) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11434) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11437) {
                          if (ch < 11436) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11438) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11439) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11460) {
                    if (ch < 11450) {
                      if (ch < 11445) {
                        if (ch < 11442) {
                          if (ch < 11441) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11443) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11444) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11447) {
                          if (ch < 11446) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11448) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11449) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11455) {
                        if (ch < 11452) {
                          if (ch < 11451) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11453) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11454) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11457) {
                          if (ch < 11456) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11458) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11459) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11470) {
                      if (ch < 11465) {
                        if (ch < 11462) {
                          if (ch < 11461) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11463) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11464) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11467) {
                          if (ch < 11466) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11468) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11469) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11475) {
                        if (ch < 11472) {
                          if (ch < 11471) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11473) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11474) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11477) {
                          if (ch < 11476) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11478) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11479) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 11789) {
                  if (ch < 11513) {
                    if (ch < 11490) {
                      if (ch < 11485) {
                        if (ch < 11482) {
                          if (ch < 11481) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11483) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11484) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11487) {
                          if (ch < 11486) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11488) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11489) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11501) {
                        if (ch < 11493) {
                          if (ch < 11491) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11499) {
                            counts[so] += 1;
                          } else {
                            if (ch < 11500) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11503) {
                          if (ch < 11502) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11506) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 11507) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11776) {
                      if (ch < 11631) {
                        if (ch < 11518) {
                          if (ch < 11517) {
                            counts[po] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 11520) {
                            counts[po] += 1;
                          } else {
                            if (ch < 11568) {
                              counts[ll] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11647) {
                          if (ch < 11632) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 11648) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 11744) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11782) {
                        if (ch < 11779) {
                          if (ch < 11778) {
                            counts[po] += 1;
                          } else {
                            counts[pi] += 1;
                          }
                        } else {
                          if (ch < 11780) {
                            counts[pf] += 1;
                          } else {
                            if (ch < 11781) {
                              counts[pi] += 1;
                            } else {
                              counts[pf] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11786) {
                          if (ch < 11785) {
                            counts[po] += 1;
                          } else {
                            counts[pi] += 1;
                          }
                        } else {
                          if (ch < 11787) {
                            counts[pf] += 1;
                          } else {
                            if (ch < 11788) {
                              counts[po] += 1;
                            } else {
                              counts[pi] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11823) {
                    if (ch < 11809) {
                      if (ch < 11803) {
                        if (ch < 11799) {
                          if (ch < 11790) {
                            counts[pf] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 11800) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 11802) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11805) {
                          if (ch < 11804) {
                            counts[po] += 1;
                          } else {
                            counts[pi] += 1;
                          }
                        } else {
                          if (ch < 11806) {
                            counts[pf] += 1;
                          } else {
                            if (ch < 11808) {
                              counts[po] += 1;
                            } else {
                              counts[pi] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11814) {
                        if (ch < 11811) {
                          if (ch < 11810) {
                            counts[pf] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 11812) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 11813) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11816) {
                          if (ch < 11815) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 11817) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 11818) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12292) {
                      if (ch < 11841) {
                        if (ch < 11834) {
                          if (ch < 11824) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 11836) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 11840) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11904) {
                          if (ch < 11842) {
                            counts[po] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 12288) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12289) {
                              counts[zs] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12297) {
                        if (ch < 12294) {
                          if (ch < 12293) {
                            counts[so] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 12295) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 12296) {
                              counts[nl] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12299) {
                          if (ch < 12298) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 12300) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 12301) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 42570) {
                if (ch < 12694) {
                  if (ch < 12336) {
                    if (ch < 12313) {
                      if (ch < 12308) {
                        if (ch < 12304) {
                          if (ch < 12303) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 12305) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 12306) {
                              counts[pe] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12310) {
                          if (ch < 12309) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 12311) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 12312) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12318) {
                        if (ch < 12315) {
                          if (ch < 12314) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 12316) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 12317) {
                              counts[pd] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12321) {
                          if (ch < 12320) {
                            counts[pe] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 12330) {
                            counts[nl] += 1;
                          } else {
                            if (ch < 12334) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12443) {
                      if (ch < 12348) {
                        if (ch < 12342) {
                          if (ch < 12337) {
                            counts[pd] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 12344) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12347) {
                              counts[nl] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12350) {
                          if (ch < 12349) {
                            counts[lo] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 12353) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12441) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12539) {
                        if (ch < 12447) {
                          if (ch < 12445) {
                            counts[sk] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 12448) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 12449) {
                              counts[pd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12543) {
                          if (ch < 12540) {
                            counts[po] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 12688) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 12690) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 42128) {
                    if (ch < 12896) {
                      if (ch < 12832) {
                        if (ch < 12736) {
                          if (ch < 12704) {
                            counts[so] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 12784) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12800) {
                              counts[lo] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12872) {
                          if (ch < 12842) {
                            counts[no] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 12880) {
                            counts[no] += 1;
                          } else {
                            if (ch < 12881) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 13312) {
                        if (ch < 12938) {
                          if (ch < 12928) {
                            counts[so] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 12977) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12992) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 19968) {
                          if (ch < 19904) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 40981) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 40982) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42560) {
                      if (ch < 42508) {
                        if (ch < 42232) {
                          if (ch < 42192) {
                            counts[so] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 42238) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 42240) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42512) {
                          if (ch < 42509) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 42528) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 42538) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42565) {
                        if (ch < 42562) {
                          if (ch < 42561) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42563) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42564) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42567) {
                          if (ch < 42566) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42568) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42569) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 42612) {
                  if (ch < 42590) {
                    if (ch < 42580) {
                      if (ch < 42575) {
                        if (ch < 42572) {
                          if (ch < 42571) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42573) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42574) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42577) {
                          if (ch < 42576) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42578) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42579) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42585) {
                        if (ch < 42582) {
                          if (ch < 42581) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42583) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42584) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42587) {
                          if (ch < 42586) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42588) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42589) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42600) {
                      if (ch < 42595) {
                        if (ch < 42592) {
                          if (ch < 42591) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42593) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42594) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42597) {
                          if (ch < 42596) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42598) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42599) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42605) {
                        if (ch < 42602) {
                          if (ch < 42601) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42603) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42604) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42607) {
                          if (ch < 42606) {
                            counts[ll] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 42608) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 42611) {
                              counts[me] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 42641) {
                    if (ch < 42631) {
                      if (ch < 42626) {
                        if (ch < 42623) {
                          if (ch < 42622) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 42624) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 42625) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42628) {
                          if (ch < 42627) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42629) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42630) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42636) {
                        if (ch < 42633) {
                          if (ch < 42632) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42634) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42635) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42638) {
                          if (ch < 42637) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42639) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42640) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42651) {
                      if (ch < 42646) {
                        if (ch < 42643) {
                          if (ch < 42642) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42644) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42645) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42648) {
                          if (ch < 42647) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42649) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42650) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42736) {
                        if (ch < 42655) {
                          if (ch < 42652) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 42656) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 42726) {
                              counts[lo] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42752) {
                          if (ch < 42738) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 42775) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 42784) {
                              counts[lm] += 1;
                            } else {
                              counts[sk] += 1;
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
          if (ch < 65342) {
            if (ch < 43359) {
              if (ch < 42875) {
                if (ch < 42828) {
                  if (ch < 42808) {
                    if (ch < 42796) {
                      if (ch < 42791) {
                        if (ch < 42788) {
                          if (ch < 42787) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42789) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42790) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42793) {
                          if (ch < 42792) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42794) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42795) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42803) {
                        if (ch < 42798) {
                          if (ch < 42797) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42799) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42802) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42805) {
                          if (ch < 42804) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42806) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42807) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42818) {
                      if (ch < 42813) {
                        if (ch < 42810) {
                          if (ch < 42809) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42811) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42812) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42815) {
                          if (ch < 42814) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42816) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42817) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42823) {
                        if (ch < 42820) {
                          if (ch < 42819) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42821) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42822) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42825) {
                          if (ch < 42824) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42826) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42827) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 42848) {
                    if (ch < 42838) {
                      if (ch < 42833) {
                        if (ch < 42830) {
                          if (ch < 42829) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42831) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42832) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42835) {
                          if (ch < 42834) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42836) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42837) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42843) {
                        if (ch < 42840) {
                          if (ch < 42839) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42841) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42842) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42845) {
                          if (ch < 42844) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42846) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42847) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42858) {
                      if (ch < 42853) {
                        if (ch < 42850) {
                          if (ch < 42849) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42851) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42852) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42855) {
                          if (ch < 42854) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42856) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42857) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42863) {
                        if (ch < 42860) {
                          if (ch < 42859) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42861) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42862) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42865) {
                          if (ch < 42864) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 42873) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42874) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 42920) {
                  if (ch < 42898) {
                    if (ch < 42886) {
                      if (ch < 42881) {
                        if (ch < 42877) {
                          if (ch < 42876) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42879) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42880) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42883) {
                          if (ch < 42882) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42884) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42885) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42892) {
                        if (ch < 42888) {
                          if (ch < 42887) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42889) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 42891) {
                              counts[sk] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42894) {
                          if (ch < 42893) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42896) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42897) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42910) {
                      if (ch < 42905) {
                        if (ch < 42902) {
                          if (ch < 42899) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42903) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42904) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42907) {
                          if (ch < 42906) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42908) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42909) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42915) {
                        if (ch < 42912) {
                          if (ch < 42911) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42913) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42914) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42917) {
                          if (ch < 42916) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42918) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42919) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 43065) {
                    if (ch < 43015) {
                      if (ch < 43002) {
                        if (ch < 42922) {
                          if (ch < 42921) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42999) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 43000) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43010) {
                          if (ch < 43003) {
                            counts[ll] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43011) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43014) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43047) {
                        if (ch < 43020) {
                          if (ch < 43019) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43043) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43045) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43056) {
                          if (ch < 43048) {
                            counts[mc] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 43062) {
                            counts[no] += 1;
                          } else {
                            if (ch < 43064) {
                              counts[so] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43250) {
                      if (ch < 43188) {
                        if (ch < 43124) {
                          if (ch < 43072) {
                            counts[so] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43136) {
                            counts[po] += 1;
                          } else {
                            if (ch < 43138) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43214) {
                          if (ch < 43204) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43216) {
                            counts[po] += 1;
                          } else {
                            if (ch < 43232) {
                              counts[nd] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43302) {
                        if (ch < 43259) {
                          if (ch < 43256) {
                            counts[lo] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 43264) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43274) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43312) {
                          if (ch < 43310) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 43335) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43346) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 57344) {
                if (ch < 43645) {
                  if (ch < 43514) {
                    if (ch < 43453) {
                      if (ch < 43443) {
                        if (ch < 43392) {
                          if (ch < 43360) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43395) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43396) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43446) {
                          if (ch < 43444) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 43450) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43452) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43488) {
                        if (ch < 43471) {
                          if (ch < 43457) {
                            counts[mc] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 43472) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 43486) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43494) {
                          if (ch < 43493) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43495) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 43504) {
                              counts[lo] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43597) {
                      if (ch < 43573) {
                        if (ch < 43567) {
                          if (ch < 43561) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43569) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 43571) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43587) {
                          if (ch < 43584) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43588) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43596) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43633) {
                        if (ch < 43612) {
                          if (ch < 43600) {
                            counts[mc] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 43616) {
                            counts[po] += 1;
                          } else {
                            if (ch < 43632) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43642) {
                          if (ch < 43639) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 43643) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43644) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 43763) {
                    if (ch < 43713) {
                      if (ch < 43701) {
                        if (ch < 43696) {
                          if (ch < 43646) {
                            counts[mc] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43697) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43698) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43705) {
                          if (ch < 43703) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43710) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43712) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43755) {
                        if (ch < 43741) {
                          if (ch < 43714) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43742) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 43744) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43758) {
                          if (ch < 43756) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43760) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 43762) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 44005) {
                      if (ch < 43867) {
                        if (ch < 43766) {
                          if (ch < 43765) {
                            counts[lm] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 43777) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43824) {
                              counts[lo] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43876) {
                          if (ch < 43868) {
                            counts[sk] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 43968) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 44003) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 44012) {
                        if (ch < 44008) {
                          if (ch < 44006) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 44009) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 44011) {
                              counts[mc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 44016) {
                          if (ch < 44013) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 44032) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 55296) {
                              counts[lo] += 1;
                            } else {
                              counts[cs] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 65093) {
                  if (ch < 65056) {
                    if (ch < 64830) {
                      if (ch < 64287) {
                        if (ch < 64256) {
                          if (ch < 63744) {
                            counts[co] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 64285) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 64286) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 64298) {
                          if (ch < 64297) {
                            counts[lo] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 64434) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 64467) {
                              counts[sk] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65024) {
                        if (ch < 64848) {
                          if (ch < 64831) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65020) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 65021) {
                              counts[sc] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65047) {
                          if (ch < 65040) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 65048) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65049) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65083) {
                      if (ch < 65078) {
                        if (ch < 65073) {
                          if (ch < 65072) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 65075) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 65077) {
                              counts[pc] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65080) {
                          if (ch < 65079) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65081) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65082) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65088) {
                        if (ch < 65085) {
                          if (ch < 65084) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 65086) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65087) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65090) {
                          if (ch < 65089) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65091) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65092) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 65136) {
                    if (ch < 65116) {
                      if (ch < 65104) {
                        if (ch < 65096) {
                          if (ch < 65095) {
                            counts[po] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65097) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65101) {
                              counts[po] += 1;
                            } else {
                              counts[pc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65113) {
                          if (ch < 65112) {
                            counts[po] += 1;
                          } else {
                            counts[pd] += 1;
                          }
                        } else {
                          if (ch < 65114) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65115) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65123) {
                        if (ch < 65118) {
                          if (ch < 65117) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65119) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65122) {
                              counts[po] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65128) {
                          if (ch < 65124) {
                            counts[pd] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 65129) {
                            counts[po] += 1;
                          } else {
                            if (ch < 65130) {
                              counts[sc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65293) {
                      if (ch < 65288) {
                        if (ch < 65281) {
                          if (ch < 65279) {
                            counts[lo] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 65284) {
                            counts[po] += 1;
                          } else {
                            if (ch < 65285) {
                              counts[sc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65290) {
                          if (ch < 65289) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 65291) {
                            counts[po] += 1;
                          } else {
                            if (ch < 65292) {
                              counts[sm] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65311) {
                        if (ch < 65296) {
                          if (ch < 65294) {
                            counts[pd] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 65306) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 65308) {
                              counts[po] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65339) {
                          if (ch < 65313) {
                            counts[po] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 65340) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65341) {
                              counts[po] += 1;
                            } else {
                              counts[pe] += 1;
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
            if (ch < 70460) {
              if (ch < 68192) {
                if (ch < 66272) {
                  if (ch < 65506) {
                    if (ch < 65377) {
                      if (ch < 65372) {
                        if (ch < 65344) {
                          if (ch < 65343) {
                            counts[sk] += 1;
                          } else {
                            counts[pc] += 1;
                          }
                        } else {
                          if (ch < 65345) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 65371) {
                              counts[ll] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65374) {
                          if (ch < 65373) {
                            counts[sm] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 65375) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 65376) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65392) {
                        if (ch < 65379) {
                          if (ch < 65378) {
                            counts[po] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65380) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65382) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65438) {
                          if (ch < 65393) {
                            counts[lm] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 65440) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 65504) {
                              counts[lo] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65792) {
                      if (ch < 65513) {
                        if (ch < 65508) {
                          if (ch < 65507) {
                            counts[sm] += 1;
                          } else {
                            counts[sk] += 1;
                          }
                        } else {
                          if (ch < 65509) {
                            counts[so] += 1;
                          } else {
                            if (ch < 65512) {
                              counts[sc] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65529) {
                          if (ch < 65517) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 65532) {
                            counts[cf] += 1;
                          } else {
                            if (ch < 65536) {
                              counts[so] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65913) {
                        if (ch < 65847) {
                          if (ch < 65799) {
                            counts[po] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 65856) {
                            counts[so] += 1;
                          } else {
                            if (ch < 65909) {
                              counts[nl] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65932) {
                          if (ch < 65930) {
                            counts[so] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 66045) {
                            counts[so] += 1;
                          } else {
                            if (ch < 66176) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 66927) {
                    if (ch < 66432) {
                      if (ch < 66369) {
                        if (ch < 66304) {
                          if (ch < 66273) {
                            counts[mn] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 66336) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 66352) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 66378) {
                          if (ch < 66370) {
                            counts[nl] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 66384) {
                            counts[nl] += 1;
                          } else {
                            if (ch < 66422) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 66560) {
                        if (ch < 66464) {
                          if (ch < 66463) {
                            counts[lo] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 66512) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 66513) {
                              counts[po] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 66640) {
                          if (ch < 66600) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 66720) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 66816) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 67862) {
                      if (ch < 67703) {
                        if (ch < 67671) {
                          if (ch < 67072) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 67672) {
                            counts[po] += 1;
                          } else {
                            if (ch < 67680) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 67712) {
                          if (ch < 67705) {
                            counts[so] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 67751) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 67840) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 68097) {
                        if (ch < 67872) {
                          if (ch < 67871) {
                            counts[no] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 67903) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 67968) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68152) {
                          if (ch < 68112) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 68160) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 68176) {
                              counts[no] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 69840) {
                  if (ch < 68608) {
                    if (ch < 68336) {
                      if (ch < 68288) {
                        if (ch < 68223) {
                          if (ch < 68221) {
                            counts[lo] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 68224) {
                            counts[po] += 1;
                          } else {
                            if (ch < 68253) {
                              counts[lo] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68297) {
                          if (ch < 68296) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 68325) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 68331) {
                              counts[mn] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 68448) {
                        if (ch < 68409) {
                          if (ch < 68352) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 68416) {
                            counts[po] += 1;
                          } else {
                            if (ch < 68440) {
                              counts[lo] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68480) {
                          if (ch < 68472) {
                            counts[lo] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 68505) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 68521) {
                              counts[po] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 69759) {
                      if (ch < 69635) {
                        if (ch < 69632) {
                          if (ch < 69216) {
                            counts[lo] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 69633) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 69634) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 69703) {
                          if (ch < 69688) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 69714) {
                            counts[po] += 1;
                          } else {
                            if (ch < 69734) {
                              counts[no] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 69815) {
                        if (ch < 69763) {
                          if (ch < 69762) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 69808) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 69811) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 69819) {
                          if (ch < 69817) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 69821) {
                            counts[po] += 1;
                          } else {
                            if (ch < 69822) {
                              counts[cf] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 70085) {
                    if (ch < 70003) {
                      if (ch < 69932) {
                        if (ch < 69888) {
                          if (ch < 69872) {
                            counts[lo] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 69891) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 69927) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 69942) {
                          if (ch < 69933) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 69952) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 69968) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70019) {
                        if (ch < 70006) {
                          if (ch < 70004) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 70016) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70018) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70070) {
                          if (ch < 70067) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 70079) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70081) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70198) {
                      if (ch < 70188) {
                        if (ch < 70106) {
                          if (ch < 70096) {
                            counts[po] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 70113) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70144) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70194) {
                          if (ch < 70191) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 70196) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 70197) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70371) {
                        if (ch < 70320) {
                          if (ch < 70200) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 70367) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70368) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70401) {
                          if (ch < 70384) {
                            counts[mn] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 70402) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70405) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 119141) {
                if (ch < 71339) {
                  if (ch < 70864) {
                    if (ch < 70835) {
                      if (ch < 70493) {
                        if (ch < 70462) {
                          if (ch < 70461) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 70464) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 70465) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70502) {
                          if (ch < 70498) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 70784) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70832) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70849) {
                        if (ch < 70842) {
                          if (ch < 70841) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 70843) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70847) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70852) {
                          if (ch < 70850) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 70854) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70855) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 71216) {
                      if (ch < 71100) {
                        if (ch < 71087) {
                          if (ch < 71040) {
                            counts[nd] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 71090) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 71096) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71103) {
                          if (ch < 71102) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 71105) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 71168) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 71231) {
                        if (ch < 71227) {
                          if (ch < 71219) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 71229) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 71230) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71236) {
                          if (ch < 71233) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 71248) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 71296) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 92917) {
                    if (ch < 71904) {
                      if (ch < 71350) {
                        if (ch < 71341) {
                          if (ch < 71340) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 71342) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 71344) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71360) {
                          if (ch < 71351) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 71840) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 71872) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 77824) {
                        if (ch < 71935) {
                          if (ch < 71914) {
                            counts[nd] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 74752) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 74864) {
                              counts[nl] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 92782) {
                          if (ch < 92768) {
                            counts[lo] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 92880) {
                            counts[po] += 1;
                          } else {
                            if (ch < 92912) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 93027) {
                      if (ch < 92992) {
                        if (ch < 92976) {
                          if (ch < 92928) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 92983) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 92988) {
                              counts[po] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 92997) {
                          if (ch < 92996) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 93008) {
                            counts[so] += 1;
                          } else {
                            if (ch < 93019) {
                              counts[nd] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 113820) {
                        if (ch < 94095) {
                          if (ch < 94033) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 94099) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 110592) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 113823) {
                          if (ch < 113821) {
                            counts[so] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 113824) {
                            counts[po] += 1;
                          } else {
                            if (ch < 118784) {
                              counts[cf] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 120488) {
                  if (ch < 119964) {
                    if (ch < 119214) {
                      if (ch < 119163) {
                        if (ch < 119146) {
                          if (ch < 119143) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 119149) {
                            counts[so] += 1;
                          } else {
                            if (ch < 119155) {
                              counts[mc] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 119173) {
                          if (ch < 119171) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 119180) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 119210) {
                              counts[so] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 119834) {
                        if (ch < 119365) {
                          if (ch < 119362) {
                            counts[so] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 119648) {
                            counts[so] += 1;
                          } else {
                            if (ch < 119808) {
                              counts[no] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 119886) {
                          if (ch < 119860) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 119912) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 119938) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 120224) {
                      if (ch < 120094) {
                        if (ch < 120016) {
                          if (ch < 119990) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 120042) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120068) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120146) {
                          if (ch < 120120) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 120172) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120198) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 120354) {
                        if (ch < 120276) {
                          if (ch < 120250) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 120302) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120328) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120406) {
                          if (ch < 120380) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 120432) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120458) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 120720) {
                    if (ch < 120604) {
                      if (ch < 120546) {
                        if (ch < 120514) {
                          if (ch < 120513) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120539) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120540) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120572) {
                          if (ch < 120571) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120597) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120598) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 120662) {
                        if (ch < 120630) {
                          if (ch < 120629) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120655) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120656) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120688) {
                          if (ch < 120687) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120713) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120714) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 125136) {
                      if (ch < 120778) {
                        if (ch < 120746) {
                          if (ch < 120745) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120771) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120772) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120782) {
                          if (ch < 120779) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 124928) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 125127) {
                              counts[lo] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 127248) {
                        if (ch < 126704) {
                          if (ch < 126464) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 126976) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 127232) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 917760) {
                          if (ch < 131072) {
                            counts[so] += 1;
                          } else {
                            if (ch < 917505) {
                              counts[lo] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        } else {
                          if (ch < 983040) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1114110) {
                              counts[co] += 1;
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
  }

  if (count_ascii)
    printf("%lu\t%s\n", ascii_cnt, long_names ? "ASCII" : "As");
  for (i = 0; i < 30; ++i) {
    if (counts[i] > 0) {
      if (long_names)
        printf("%lu\t%s\n", counts[i], long_categories[i]);
      else
        printf("%lu\t%s\n", counts[i], categories[i]);
    }
  }

  if (ferror(stdin)) {
    perror("error reading from standard input: ");
    return 1;
  }
  return 0;
}
