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
  fprintf(stderr, "USAGE: utf8-category [--count-ascii | --skip-ascii]\n");
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
    if (skip_ascii && iswascii(ch))
      continue;
    if (count_ascii && iswascii(ch)) {
      ++ascii_cnt;
      continue;
    }
    if (ch < 128) {
      if (ch < 59) {
        if (ch < 41) {
          if (ch < 35) {
            if (ch < 31) {
              counts[cc] += 1;
            } else {
              if (ch < 32) {
                counts[zs] += 1;
              } else {
                counts[po] += 1;
              }
            }
          } else {
            if (ch < 39) {
              if (ch < 36) {
                counts[sc] += 1;
              } else {
                counts[po] += 1;
              }
            } else {
              if (ch < 40) {
                counts[ps] += 1;
              } else {
                counts[pe] += 1;
              }
            }
          }
        } else {
          if (ch < 44) {
            if (ch < 42) {
              counts[po] += 1;
            } else {
              if (ch < 43) {
                counts[sm] += 1;
              } else {
                counts[po] += 1;
              }
            }
          } else {
            if (ch < 47) {
              if (ch < 45) {
                counts[pd] += 1;
              } else {
                counts[po] += 1;
              }
            } else {
              if (ch < 57) {
                counts[nd] += 1;
              } else {
                counts[po] += 1;
              }
            }
          }
        }
      } else {
        if (ch < 94) {
          if (ch < 90) {
            if (ch < 62) {
              counts[sm] += 1;
            } else {
              if (ch < 64) {
                counts[po] += 1;
              } else {
                counts[lu] += 1;
              }
            }
          } else {
            if (ch < 92) {
              if (ch < 91) {
                counts[ps] += 1;
              } else {
                counts[po] += 1;
              }
            } else {
              if (ch < 93) {
                counts[pe] += 1;
              } else {
                counts[sk] += 1;
              }
            }
          }
        } else {
          if (ch < 123) {
            if (ch < 96) {
              if (ch < 95) {
                counts[pc] += 1;
              } else {
                counts[sk] += 1;
              }
            } else {
              if (ch < 122) {
                counts[ll] += 1;
              } else {
                counts[ps] += 1;
              }
            }
          } else {
            if (ch < 125) {
              if (ch < 124) {
                counts[sm] += 1;
              } else {
                counts[pe] += 1;
              }
            } else {
              if (ch < 126) {
                counts[sm] += 1;
              } else {
                counts[cc] += 1;
              }
            }
          }
        }
      }
    } else {
      if (ch < 7894) {
        if (ch < 1785) {
          if (ch < 659) {
            if (ch < 389) {
              if (ch < 303) {
                if (ch < 263) {
                  if (ch < 183) {
                    if (ch < 171) {
                      if (ch < 166) {
                        if (ch < 160) {
                          if (ch < 159) {
                            counts[cc] += 1;
                          } else {
                            counts[zs] += 1;
                          }
                        } else {
                          if (ch < 161) {
                            counts[po] += 1;
                          } else {
                            if (ch < 165) {
                              counts[sc] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 168) {
                          if (ch < 167) {
                            counts[po] += 1;
                          } else {
                            counts[sk] += 1;
                          }
                        } else {
                          if (ch < 169) {
                            counts[so] += 1;
                          } else {
                            if (ch < 170) {
                              counts[lo] += 1;
                            } else {
                              counts[pi] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 176) {
                        if (ch < 173) {
                          if (ch < 172) {
                            counts[sm] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 174) {
                            counts[so] += 1;
                          } else {
                            if (ch < 175) {
                              counts[sk] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 179) {
                          if (ch < 177) {
                            counts[sm] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 180) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 181) {
                              counts[ll] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 246) {
                      if (ch < 190) {
                        if (ch < 185) {
                          if (ch < 184) {
                            counts[sk] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 186) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 187) {
                              counts[pf] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 214) {
                          if (ch < 191) {
                            counts[po] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 215) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 222) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 258) {
                        if (ch < 255) {
                          if (ch < 247) {
                            counts[sm] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 256) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 257) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 260) {
                          if (ch < 259) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 261) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 262) {
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
                  if (ch < 283) {
                    if (ch < 273) {
                      if (ch < 268) {
                        if (ch < 265) {
                          if (ch < 264) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 266) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 267) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 270) {
                          if (ch < 269) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 271) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 272) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 278) {
                        if (ch < 275) {
                          if (ch < 274) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 276) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 277) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 280) {
                          if (ch < 279) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 281) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 282) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 293) {
                      if (ch < 288) {
                        if (ch < 285) {
                          if (ch < 284) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 286) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 287) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 290) {
                          if (ch < 289) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 291) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 292) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 298) {
                        if (ch < 295) {
                          if (ch < 294) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 296) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 297) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 300) {
                          if (ch < 299) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 301) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 302) {
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
                if (ch < 345) {
                  if (ch < 324) {
                    if (ch < 314) {
                      if (ch < 308) {
                        if (ch < 305) {
                          if (ch < 304) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 306) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 307) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 310) {
                          if (ch < 309) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 312) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 313) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 319) {
                        if (ch < 316) {
                          if (ch < 315) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 317) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 318) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 321) {
                          if (ch < 320) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 322) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 323) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 335) {
                      if (ch < 330) {
                        if (ch < 326) {
                          if (ch < 325) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 327) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 329) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 332) {
                          if (ch < 331) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 333) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 334) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 340) {
                        if (ch < 337) {
                          if (ch < 336) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 338) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 339) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 342) {
                          if (ch < 341) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 343) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 344) {
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
                  if (ch < 365) {
                    if (ch < 355) {
                      if (ch < 350) {
                        if (ch < 347) {
                          if (ch < 346) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 348) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 349) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 352) {
                          if (ch < 351) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 353) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 354) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 360) {
                        if (ch < 357) {
                          if (ch < 356) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 358) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 359) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 362) {
                          if (ch < 361) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 363) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 364) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 375) {
                      if (ch < 370) {
                        if (ch < 367) {
                          if (ch < 366) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 368) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 369) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 372) {
                          if (ch < 371) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 373) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 374) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 381) {
                        if (ch < 378) {
                          if (ch < 377) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 379) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 380) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 386) {
                          if (ch < 384) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 387) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 388) {
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
              if (ch < 497) {
                if (ch < 455) {
                  if (ch < 424) {
                    if (ch < 411) {
                      if (ch < 401) {
                        if (ch < 392) {
                          if (ch < 391) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 395) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 397) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 404) {
                          if (ch < 402) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 405) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 408) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 418) {
                        if (ch < 414) {
                          if (ch < 413) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 416) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 417) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 420) {
                          if (ch < 419) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 421) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 423) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 438) {
                      if (ch < 431) {
                        if (ch < 427) {
                          if (ch < 425) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 428) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 429) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 435) {
                          if (ch < 432) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 436) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 437) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 447) {
                        if (ch < 442) {
                          if (ch < 440) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 443) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 444) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 452) {
                          if (ch < 451) {
                            counts[lo] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 453) {
                            counts[lt] += 1;
                          } else {
                            if (ch < 454) {
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
                  if (ch < 475) {
                    if (ch < 465) {
                      if (ch < 460) {
                        if (ch < 457) {
                          if (ch < 456) {
                            counts[lt] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 458) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 459) {
                              counts[lt] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 462) {
                          if (ch < 461) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 463) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 464) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 470) {
                        if (ch < 467) {
                          if (ch < 466) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 468) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 469) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 472) {
                          if (ch < 471) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 473) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 474) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 486) {
                      if (ch < 481) {
                        if (ch < 478) {
                          if (ch < 477) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 479) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 480) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 483) {
                          if (ch < 482) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 484) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 485) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 491) {
                        if (ch < 488) {
                          if (ch < 487) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 489) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 490) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 493) {
                          if (ch < 492) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 494) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 496) {
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
                if (ch < 539) {
                  if (ch < 519) {
                    if (ch < 509) {
                      if (ch < 504) {
                        if (ch < 499) {
                          if (ch < 498) {
                            counts[lt] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 500) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 501) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 506) {
                          if (ch < 505) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 507) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 508) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 514) {
                        if (ch < 511) {
                          if (ch < 510) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 512) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 513) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 516) {
                          if (ch < 515) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 517) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 518) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 529) {
                      if (ch < 524) {
                        if (ch < 521) {
                          if (ch < 520) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 522) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 523) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 526) {
                          if (ch < 525) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 527) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 528) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 534) {
                        if (ch < 531) {
                          if (ch < 530) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 532) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 533) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 536) {
                          if (ch < 535) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 537) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 538) {
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
                  if (ch < 559) {
                    if (ch < 549) {
                      if (ch < 544) {
                        if (ch < 541) {
                          if (ch < 540) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 542) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 543) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 546) {
                          if (ch < 545) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 547) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 548) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 554) {
                        if (ch < 551) {
                          if (ch < 550) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 552) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 553) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 556) {
                          if (ch < 555) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 557) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 558) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 578) {
                      if (ch < 571) {
                        if (ch < 561) {
                          if (ch < 560) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 562) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 569) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 574) {
                          if (ch < 572) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 576) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 577) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 586) {
                        if (ch < 583) {
                          if (ch < 582) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 584) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 585) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 588) {
                          if (ch < 587) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 589) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 590) {
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
            if (ch < 1215) {
              if (ch < 1130) {
                if (ch < 987) {
                  if (ch < 886) {
                    if (ch < 749) {
                      if (ch < 721) {
                        if (ch < 687) {
                          if (ch < 660) {
                            counts[lo] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 705) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 709) {
                              counts[sk] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 740) {
                          if (ch < 735) {
                            counts[sk] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 747) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 748) {
                              counts[lm] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 881) {
                        if (ch < 767) {
                          if (ch < 750) {
                            counts[lm] += 1;
                          } else {
                            counts[sk] += 1;
                          }
                        } else {
                          if (ch < 879) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 880) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 883) {
                          if (ch < 882) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 884) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 885) {
                              counts[sk] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 912) {
                      if (ch < 895) {
                        if (ch < 890) {
                          if (ch < 887) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 893) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 894) {
                              counts[po] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 902) {
                          if (ch < 901) {
                            counts[sk] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 903) {
                            counts[po] += 1;
                          } else {
                            if (ch < 911) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 980) {
                        if (ch < 974) {
                          if (ch < 939) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 975) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 977) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 984) {
                          if (ch < 983) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 985) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 986) {
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
                  if (ch < 1011) {
                    if (ch < 997) {
                      if (ch < 992) {
                        if (ch < 989) {
                          if (ch < 988) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 990) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 991) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 994) {
                          if (ch < 993) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 995) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 996) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1002) {
                        if (ch < 999) {
                          if (ch < 998) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1000) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1001) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1004) {
                          if (ch < 1003) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1005) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1006) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1120) {
                      if (ch < 1016) {
                        if (ch < 1013) {
                          if (ch < 1012) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1014) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 1015) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1020) {
                          if (ch < 1018) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1071) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1119) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1125) {
                        if (ch < 1122) {
                          if (ch < 1121) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1123) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1124) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1127) {
                          if (ch < 1126) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1128) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1129) {
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
                if (ch < 1175) {
                  if (ch < 1150) {
                    if (ch < 1140) {
                      if (ch < 1135) {
                        if (ch < 1132) {
                          if (ch < 1131) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1133) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1134) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1137) {
                          if (ch < 1136) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1138) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1139) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1145) {
                        if (ch < 1142) {
                          if (ch < 1141) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1143) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1144) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1147) {
                          if (ch < 1146) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1148) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1149) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1165) {
                      if (ch < 1159) {
                        if (ch < 1152) {
                          if (ch < 1151) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1153) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1154) {
                              counts[so] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1162) {
                          if (ch < 1161) {
                            counts[me] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1163) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1164) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1170) {
                        if (ch < 1167) {
                          if (ch < 1166) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1168) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1169) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1172) {
                          if (ch < 1171) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1173) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1174) {
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
                  if (ch < 1195) {
                    if (ch < 1185) {
                      if (ch < 1180) {
                        if (ch < 1177) {
                          if (ch < 1176) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1178) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1179) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1182) {
                          if (ch < 1181) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1183) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1184) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1190) {
                        if (ch < 1187) {
                          if (ch < 1186) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1188) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1189) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1192) {
                          if (ch < 1191) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1193) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1194) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1205) {
                      if (ch < 1200) {
                        if (ch < 1197) {
                          if (ch < 1196) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1198) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1199) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1202) {
                          if (ch < 1201) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1203) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1204) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1210) {
                        if (ch < 1207) {
                          if (ch < 1206) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1208) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1209) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1212) {
                          if (ch < 1211) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1213) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1214) {
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
              if (ch < 1297) {
                if (ch < 1257) {
                  if (ch < 1237) {
                    if (ch < 1226) {
                      if (ch < 1221) {
                        if (ch < 1218) {
                          if (ch < 1217) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1219) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1220) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1223) {
                          if (ch < 1222) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1224) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1225) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1232) {
                        if (ch < 1228) {
                          if (ch < 1227) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1229) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1231) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1234) {
                          if (ch < 1233) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1235) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1236) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1247) {
                      if (ch < 1242) {
                        if (ch < 1239) {
                          if (ch < 1238) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1240) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1241) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1244) {
                          if (ch < 1243) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1245) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1246) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1252) {
                        if (ch < 1249) {
                          if (ch < 1248) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1250) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1251) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1254) {
                          if (ch < 1253) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1255) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1256) {
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
                  if (ch < 1277) {
                    if (ch < 1267) {
                      if (ch < 1262) {
                        if (ch < 1259) {
                          if (ch < 1258) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1260) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1261) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1264) {
                          if (ch < 1263) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1265) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1266) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1272) {
                        if (ch < 1269) {
                          if (ch < 1268) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1270) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1271) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1274) {
                          if (ch < 1273) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1275) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1276) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1287) {
                      if (ch < 1282) {
                        if (ch < 1279) {
                          if (ch < 1278) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1280) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1281) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1284) {
                          if (ch < 1283) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1285) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1286) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1292) {
                        if (ch < 1289) {
                          if (ch < 1288) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1290) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1291) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1294) {
                          if (ch < 1293) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1295) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1296) {
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
                if (ch < 1470) {
                  if (ch < 1317) {
                    if (ch < 1307) {
                      if (ch < 1302) {
                        if (ch < 1299) {
                          if (ch < 1298) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1300) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1301) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1304) {
                          if (ch < 1303) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1305) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1306) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1312) {
                        if (ch < 1309) {
                          if (ch < 1308) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1310) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1311) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1314) {
                          if (ch < 1313) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1315) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1316) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1327) {
                      if (ch < 1322) {
                        if (ch < 1319) {
                          if (ch < 1318) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 1320) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1321) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1324) {
                          if (ch < 1323) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 1325) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1326) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1417) {
                        if (ch < 1369) {
                          if (ch < 1366) {
                            counts[lu] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 1375) {
                            counts[po] += 1;
                          } else {
                            if (ch < 1415) {
                              counts[ll] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1422) {
                          if (ch < 1418) {
                            counts[pd] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 1423) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 1469) {
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
                  if (ch < 1599) {
                    if (ch < 1541) {
                      if (ch < 1477) {
                        if (ch < 1472) {
                          if (ch < 1471) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 1474) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1475) {
                              counts[po] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1479) {
                          if (ch < 1478) {
                            counts[po] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 1522) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1524) {
                              counts[po] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1551) {
                        if (ch < 1546) {
                          if (ch < 1544) {
                            counts[sm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 1547) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 1549) {
                              counts[po] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1563) {
                          if (ch < 1562) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 1564) {
                            counts[cf] += 1;
                          } else {
                            if (ch < 1567) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1749) {
                      if (ch < 1645) {
                        if (ch < 1610) {
                          if (ch < 1600) {
                            counts[lm] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 1631) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1641) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1648) {
                          if (ch < 1647) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 1747) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1748) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1766) {
                        if (ch < 1757) {
                          if (ch < 1756) {
                            counts[mn] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 1758) {
                            counts[so] += 1;
                          } else {
                            if (ch < 1764) {
                              counts[mn] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1769) {
                          if (ch < 1768) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 1773) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1775) {
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
          if (ch < 6169) {
            if (ch < 3404) {
              if (ch < 2671) {
                if (ch < 2368) {
                  if (ch < 2069) {
                    if (ch < 1957) {
                      if (ch < 1807) {
                        if (ch < 1790) {
                          if (ch < 1788) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 1791) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1805) {
                              counts[po] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1809) {
                          if (ch < 1808) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 1839) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1866) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2035) {
                        if (ch < 1969) {
                          if (ch < 1968) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 1993) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 2026) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2038) {
                          if (ch < 2037) {
                            counts[lm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 2041) {
                            counts[po] += 1;
                          } else {
                            if (ch < 2042) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2139) {
                      if (ch < 2087) {
                        if (ch < 2074) {
                          if (ch < 2073) {
                            counts[mn] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 2083) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2084) {
                              counts[lm] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2093) {
                          if (ch < 2088) {
                            counts[lm] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2110) {
                            counts[po] += 1;
                          } else {
                            if (ch < 2136) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2361) {
                        if (ch < 2226) {
                          if (ch < 2142) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2306) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2307) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2363) {
                          if (ch < 2362) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 2364) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2365) {
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
                  if (ch < 2500) {
                    if (ch < 2415) {
                      if (ch < 2384) {
                        if (ch < 2380) {
                          if (ch < 2376) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 2381) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2383) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2401) {
                          if (ch < 2391) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2403) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2405) {
                              counts[po] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2435) {
                        if (ch < 2417) {
                          if (ch < 2416) {
                            counts[po] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 2432) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2433) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2492) {
                          if (ch < 2489) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2493) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2496) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2553) {
                      if (ch < 2529) {
                        if (ch < 2509) {
                          if (ch < 2508) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2510) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2519) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2543) {
                          if (ch < 2531) {
                            counts[mn] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 2545) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2547) {
                              counts[sc] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2617) {
                        if (ch < 2555) {
                          if (ch < 2554) {
                            counts[so] += 1;
                          } else {
                            counts[sc] += 1;
                          }
                        } else {
                          if (ch < 2562) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2563) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2624) {
                          if (ch < 2620) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 2641) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2654) {
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
                if (ch < 3021) {
                  if (ch < 2876) {
                    if (ch < 2764) {
                      if (ch < 2745) {
                        if (ch < 2676) {
                          if (ch < 2673) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2690) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2691) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2749) {
                          if (ch < 2748) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2752) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2760) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2800) {
                        if (ch < 2785) {
                          if (ch < 2765) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 2787) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2799) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2817) {
                          if (ch < 2801) {
                            counts[sc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2819) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2873) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2915) {
                      if (ch < 2884) {
                        if (ch < 2878) {
                          if (ch < 2877) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 2879) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2880) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2902) {
                          if (ch < 2892) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 2903) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2913) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2946) {
                        if (ch < 2928) {
                          if (ch < 2927) {
                            counts[nd] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 2929) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2935) {
                              counts[no] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3007) {
                          if (ch < 3001) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 3008) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3020) {
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
                  if (ch < 3203) {
                    if (ch < 3133) {
                      if (ch < 3064) {
                        if (ch < 3031) {
                          if (ch < 3024) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 3055) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 3058) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3066) {
                          if (ch < 3065) {
                            counts[sc] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 3072) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3075) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3171) {
                        if (ch < 3140) {
                          if (ch < 3136) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 3158) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3169) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3198) {
                          if (ch < 3183) {
                            counts[nd] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 3199) {
                            counts[so] += 1;
                          } else {
                            if (ch < 3201) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3286) {
                      if (ch < 3263) {
                        if (ch < 3260) {
                          if (ch < 3257) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3261) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3262) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3270) {
                          if (ch < 3268) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3275) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3277) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3329) {
                        if (ch < 3299) {
                          if (ch < 3297) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3311) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 3314) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3389) {
                          if (ch < 3331) {
                            counts[mc] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 3392) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3396) {
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
              if (ch < 4156) {
                if (ch < 3858) {
                  if (ch < 3633) {
                    if (ch < 3459) {
                      if (ch < 3427) {
                        if (ch < 3406) {
                          if (ch < 3405) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 3415) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3425) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3445) {
                          if (ch < 3439) {
                            counts[nd] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 3449) {
                            counts[so] += 1;
                          } else {
                            if (ch < 3455) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3551) {
                        if (ch < 3530) {
                          if (ch < 3526) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3537) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3542) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3571) {
                          if (ch < 3567) {
                            counts[nd] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 3572) {
                            counts[po] += 1;
                          } else {
                            if (ch < 3632) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3760) {
                      if (ch < 3654) {
                        if (ch < 3642) {
                          if (ch < 3635) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3647) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 3653) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3663) {
                          if (ch < 3662) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 3673) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 3675) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3782) {
                        if (ch < 3763) {
                          if (ch < 3761) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 3772) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3780) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3801) {
                          if (ch < 3789) {
                            counts[mn] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 3840) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3843) {
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
                  if (ch < 3966) {
                    if (ch < 3894) {
                      if (ch < 3871) {
                        if (ch < 3860) {
                          if (ch < 3859) {
                            counts[so] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 3863) {
                            counts[so] += 1;
                          } else {
                            if (ch < 3865) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3891) {
                          if (ch < 3881) {
                            counts[nd] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 3892) {
                            counts[so] += 1;
                          } else {
                            if (ch < 3893) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3899) {
                        if (ch < 3896) {
                          if (ch < 3895) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 3897) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3898) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3901) {
                          if (ch < 3900) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 3903) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3948) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4052) {
                      if (ch < 3980) {
                        if (ch < 3972) {
                          if (ch < 3967) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 3973) {
                            counts[po] += 1;
                          } else {
                            if (ch < 3975) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4037) {
                          if (ch < 4028) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 4038) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 4047) {
                              counts[so] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4144) {
                        if (ch < 4058) {
                          if (ch < 4056) {
                            counts[so] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 4138) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 4140) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4151) {
                          if (ch < 4145) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 4152) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4154) {
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
                if (ch < 5740) {
                  if (ch < 4236) {
                    if (ch < 4193) {
                      if (ch < 4181) {
                        if (ch < 4159) {
                          if (ch < 4158) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 4169) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 4175) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4185) {
                          if (ch < 4183) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 4189) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 4192) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4212) {
                        if (ch < 4198) {
                          if (ch < 4196) {
                            counts[mc] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 4205) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4208) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4226) {
                          if (ch < 4225) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 4228) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4230) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4347) {
                      if (ch < 4252) {
                        if (ch < 4238) {
                          if (ch < 4237) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 4239) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4249) {
                              counts[nd] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4255) {
                          if (ch < 4253) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 4301) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 4346) {
                              counts[lo] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4988) {
                        if (ch < 4954) {
                          if (ch < 4348) {
                            counts[lm] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 4959) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 4968) {
                              counts[po] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 5017) {
                          if (ch < 5007) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 5108) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 5120) {
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
                  if (ch < 6069) {
                    if (ch < 5905) {
                      if (ch < 5787) {
                        if (ch < 5759) {
                          if (ch < 5742) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 5760) {
                            counts[zs] += 1;
                          } else {
                            if (ch < 5786) {
                              counts[lo] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 5866) {
                          if (ch < 5788) {
                            counts[pe] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 5869) {
                            counts[po] += 1;
                          } else {
                            if (ch < 5872) {
                              counts[nl] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 5969) {
                        if (ch < 5937) {
                          if (ch < 5908) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 5940) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 5942) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6000) {
                          if (ch < 5971) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 6003) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6067) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6107) {
                      if (ch < 6088) {
                        if (ch < 6077) {
                          if (ch < 6070) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6085) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6086) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6102) {
                          if (ch < 6099) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 6103) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 6106) {
                              counts[po] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6149) {
                        if (ch < 6109) {
                          if (ch < 6108) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6121) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 6137) {
                              counts[no] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6154) {
                          if (ch < 6150) {
                            counts[pd] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 6157) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6158) {
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
            if (ch < 7726) {
              if (ch < 7153) {
                if (ch < 6822) {
                  if (ch < 6617) {
                    if (ch < 6450) {
                      if (ch < 6430) {
                        if (ch < 6211) {
                          if (ch < 6210) {
                            counts[lo] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 6312) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6313) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6438) {
                          if (ch < 6434) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 6440) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6449) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6479) {
                        if (ch < 6459) {
                          if (ch < 6456) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6464) {
                            counts[so] += 1;
                          } else {
                            if (ch < 6469) {
                              counts[po] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6592) {
                          if (ch < 6571) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 6599) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6601) {
                              counts[mc] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6742) {
                      if (ch < 6682) {
                        if (ch < 6655) {
                          if (ch < 6618) {
                            counts[no] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 6678) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6680) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6687) {
                          if (ch < 6683) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 6740) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6741) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6756) {
                        if (ch < 6752) {
                          if (ch < 6743) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6753) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6754) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6770) {
                          if (ch < 6764) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 6783) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6809) {
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
                  if (ch < 7027) {
                    if (ch < 6970) {
                      if (ch < 6915) {
                        if (ch < 6829) {
                          if (ch < 6823) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 6845) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6846) {
                              counts[me] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6963) {
                          if (ch < 6916) {
                            counts[mc] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 6964) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6965) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6980) {
                        if (ch < 6972) {
                          if (ch < 6971) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 6977) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6978) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7001) {
                          if (ch < 6987) {
                            counts[lo] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 7008) {
                            counts[po] += 1;
                          } else {
                            if (ch < 7018) {
                              counts[so] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7085) {
                      if (ch < 7073) {
                        if (ch < 7041) {
                          if (ch < 7036) {
                            counts[so] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 7042) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 7072) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7079) {
                          if (ch < 7077) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 7081) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 7082) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7143) {
                        if (ch < 7097) {
                          if (ch < 7087) {
                            counts[lo] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 7141) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 7142) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7148) {
                          if (ch < 7145) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 7149) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 7150) {
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
                if (ch < 7686) {
                  if (ch < 7404) {
                    if (ch < 7247) {
                      if (ch < 7219) {
                        if (ch < 7167) {
                          if (ch < 7155) {
                            counts[mc] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 7203) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 7211) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7223) {
                          if (ch < 7221) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 7231) {
                            counts[po] += 1;
                          } else {
                            if (ch < 7241) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7378) {
                        if (ch < 7287) {
                          if (ch < 7257) {
                            counts[nd] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 7293) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 7367) {
                              counts[po] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7392) {
                          if (ch < 7379) {
                            counts[po] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 7393) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 7400) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7544) {
                      if (ch < 7414) {
                        if (ch < 7409) {
                          if (ch < 7405) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 7411) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 7412) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7467) {
                          if (ch < 7417) {
                            counts[mn] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7530) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 7543) {
                              counts[ll] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7681) {
                        if (ch < 7615) {
                          if (ch < 7578) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 7679) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 7680) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7683) {
                          if (ch < 7682) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7684) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7685) {
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
                  if (ch < 7706) {
                    if (ch < 7696) {
                      if (ch < 7691) {
                        if (ch < 7688) {
                          if (ch < 7687) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7689) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7690) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7693) {
                          if (ch < 7692) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7694) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7695) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7701) {
                        if (ch < 7698) {
                          if (ch < 7697) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7699) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7700) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7703) {
                          if (ch < 7702) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7704) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7705) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7716) {
                      if (ch < 7711) {
                        if (ch < 7708) {
                          if (ch < 7707) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7709) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7710) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7713) {
                          if (ch < 7712) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7714) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7715) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7721) {
                        if (ch < 7718) {
                          if (ch < 7717) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7719) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7720) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7723) {
                          if (ch < 7722) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7724) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7725) {
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
              if (ch < 7806) {
                if (ch < 7766) {
                  if (ch < 7746) {
                    if (ch < 7736) {
                      if (ch < 7731) {
                        if (ch < 7728) {
                          if (ch < 7727) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7729) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7730) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7733) {
                          if (ch < 7732) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7734) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7735) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7741) {
                        if (ch < 7738) {
                          if (ch < 7737) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7739) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7740) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7743) {
                          if (ch < 7742) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7744) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7745) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7756) {
                      if (ch < 7751) {
                        if (ch < 7748) {
                          if (ch < 7747) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7749) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7750) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7753) {
                          if (ch < 7752) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7754) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7755) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7761) {
                        if (ch < 7758) {
                          if (ch < 7757) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7759) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7760) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7763) {
                          if (ch < 7762) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7764) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7765) {
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
                  if (ch < 7786) {
                    if (ch < 7776) {
                      if (ch < 7771) {
                        if (ch < 7768) {
                          if (ch < 7767) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7769) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7770) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7773) {
                          if (ch < 7772) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7774) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7775) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7781) {
                        if (ch < 7778) {
                          if (ch < 7777) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7779) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7780) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7783) {
                          if (ch < 7782) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7784) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7785) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7796) {
                      if (ch < 7791) {
                        if (ch < 7788) {
                          if (ch < 7787) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7789) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7790) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7793) {
                          if (ch < 7792) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7794) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7795) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7801) {
                        if (ch < 7798) {
                          if (ch < 7797) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7799) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7800) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7803) {
                          if (ch < 7802) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7804) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7805) {
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
                if (ch < 7854) {
                  if (ch < 7826) {
                    if (ch < 7816) {
                      if (ch < 7811) {
                        if (ch < 7808) {
                          if (ch < 7807) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7809) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7810) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7813) {
                          if (ch < 7812) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7814) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7815) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7821) {
                        if (ch < 7818) {
                          if (ch < 7817) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7819) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7820) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7823) {
                          if (ch < 7822) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7824) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7825) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7844) {
                      if (ch < 7839) {
                        if (ch < 7828) {
                          if (ch < 7827) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7837) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7838) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7841) {
                          if (ch < 7840) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7842) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7843) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7849) {
                        if (ch < 7846) {
                          if (ch < 7845) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7847) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7848) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7851) {
                          if (ch < 7850) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7852) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7853) {
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
                  if (ch < 7874) {
                    if (ch < 7864) {
                      if (ch < 7859) {
                        if (ch < 7856) {
                          if (ch < 7855) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7857) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7858) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7861) {
                          if (ch < 7860) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7862) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7863) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7869) {
                        if (ch < 7866) {
                          if (ch < 7865) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7867) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7868) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7871) {
                          if (ch < 7870) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7872) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7873) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7884) {
                      if (ch < 7879) {
                        if (ch < 7876) {
                          if (ch < 7875) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7877) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7878) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7881) {
                          if (ch < 7880) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7882) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7883) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7889) {
                        if (ch < 7886) {
                          if (ch < 7885) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7887) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7888) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7891) {
                          if (ch < 7890) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7892) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7893) {
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
        if (ch < 42785) {
          if (ch < 11399) {
            if (ch < 8507) {
              if (ch < 8190) {
                if (ch < 7934) {
                  if (ch < 7914) {
                    if (ch < 7904) {
                      if (ch < 7899) {
                        if (ch < 7896) {
                          if (ch < 7895) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7897) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7898) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7901) {
                          if (ch < 7900) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7902) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7903) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7909) {
                        if (ch < 7906) {
                          if (ch < 7905) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7907) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7908) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7911) {
                          if (ch < 7910) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7912) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7913) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7924) {
                      if (ch < 7919) {
                        if (ch < 7916) {
                          if (ch < 7915) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7917) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7918) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7921) {
                          if (ch < 7920) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7922) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7923) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7929) {
                        if (ch < 7926) {
                          if (ch < 7925) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7927) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7928) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7931) {
                          if (ch < 7930) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7932) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7933) {
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
                  if (ch < 8111) {
                    if (ch < 8013) {
                      if (ch < 7975) {
                        if (ch < 7951) {
                          if (ch < 7943) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 7957) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7965) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7991) {
                          if (ch < 7983) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 7999) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8005) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8071) {
                        if (ch < 8031) {
                          if (ch < 8023) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8039) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8047) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8087) {
                          if (ch < 8079) {
                            counts[lt] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8095) {
                            counts[lt] += 1;
                          } else {
                            if (ch < 8103) {
                              counts[ll] += 1;
                            } else {
                              counts[lt] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8143) {
                      if (ch < 8126) {
                        if (ch < 8123) {
                          if (ch < 8119) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8124) {
                            counts[lt] += 1;
                          } else {
                            if (ch < 8125) {
                              counts[sk] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8135) {
                          if (ch < 8129) {
                            counts[sk] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8139) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8140) {
                              counts[lt] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8172) {
                        if (ch < 8155) {
                          if (ch < 8151) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8159) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 8167) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8183) {
                          if (ch < 8175) {
                            counts[sk] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8187) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8188) {
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
                if (ch < 8329) {
                  if (ch < 8254) {
                    if (ch < 8222) {
                      if (ch < 8216) {
                        if (ch < 8207) {
                          if (ch < 8202) {
                            counts[zs] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 8213) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 8215) {
                              counts[po] += 1;
                            } else {
                              counts[pi] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8218) {
                          if (ch < 8217) {
                            counts[pf] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 8220) {
                            counts[pi] += 1;
                          } else {
                            if (ch < 8221) {
                              counts[pf] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8238) {
                        if (ch < 8231) {
                          if (ch < 8223) {
                            counts[pi] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 8232) {
                            counts[zl] += 1;
                          } else {
                            if (ch < 8233) {
                              counts[zp] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8248) {
                          if (ch < 8239) {
                            counts[zs] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 8249) {
                            counts[pi] += 1;
                          } else {
                            if (ch < 8250) {
                              counts[pf] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8286) {
                      if (ch < 8262) {
                        if (ch < 8259) {
                          if (ch < 8256) {
                            counts[pc] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 8260) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8261) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8274) {
                          if (ch < 8273) {
                            counts[po] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 8275) {
                            counts[po] += 1;
                          } else {
                            if (ch < 8276) {
                              counts[pc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8313) {
                        if (ch < 8303) {
                          if (ch < 8287) {
                            counts[zs] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 8304) {
                            counts[no] += 1;
                          } else {
                            if (ch < 8305) {
                              counts[lm] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8317) {
                          if (ch < 8316) {
                            counts[sm] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 8318) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 8319) {
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
                  if (ch < 8467) {
                    if (ch < 8432) {
                      if (ch < 8381) {
                        if (ch < 8333) {
                          if (ch < 8332) {
                            counts[sm] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 8334) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 8348) {
                              counts[lm] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8416) {
                          if (ch < 8412) {
                            counts[mn] += 1;
                          } else {
                            counts[me] += 1;
                          }
                        } else {
                          if (ch < 8417) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 8420) {
                              counts[me] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8457) {
                        if (ch < 8450) {
                          if (ch < 8449) {
                            counts[so] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8454) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8455) {
                              counts[lu] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8461) {
                          if (ch < 8458) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8463) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8466) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8487) {
                      if (ch < 8477) {
                        if (ch < 8469) {
                          if (ch < 8468) {
                            counts[so] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8471) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8472) {
                              counts[sm] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8484) {
                          if (ch < 8483) {
                            counts[so] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8485) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8486) {
                              counts[lu] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8495) {
                        if (ch < 8489) {
                          if (ch < 8488) {
                            counts[lu] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 8493) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8494) {
                              counts[so] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8500) {
                          if (ch < 8499) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 8504) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 8505) {
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
              if (ch < 10175) {
                if (ch < 8971) {
                  if (ch < 8607) {
                    if (ch < 8527) {
                      if (ch < 8521) {
                        if (ch < 8511) {
                          if (ch < 8509) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 8516) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8517) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8523) {
                          if (ch < 8522) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 8525) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8526) {
                              counts[ll] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8584) {
                        if (ch < 8578) {
                          if (ch < 8543) {
                            counts[no] += 1;
                          } else {
                            counts[nl] += 1;
                          }
                        } else {
                          if (ch < 8579) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8580) {
                              counts[ll] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8596) {
                          if (ch < 8585) {
                            counts[no] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 8601) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8603) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8657) {
                      if (ch < 8614) {
                        if (ch < 8610) {
                          if (ch < 8608) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 8611) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8613) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8622) {
                          if (ch < 8621) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 8653) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8655) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8959) {
                        if (ch < 8659) {
                          if (ch < 8658) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 8660) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8691) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8968) {
                          if (ch < 8967) {
                            counts[so] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 8969) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 8970) {
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
                  if (ch < 9719) {
                    if (ch < 9179) {
                      if (ch < 9002) {
                        if (ch < 8993) {
                          if (ch < 8991) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 9000) {
                            counts[so] += 1;
                          } else {
                            if (ch < 9001) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 9084) {
                          if (ch < 9083) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 9114) {
                            counts[so] += 1;
                          } else {
                            if (ch < 9139) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 9471) {
                        if (ch < 9290) {
                          if (ch < 9185) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 9371) {
                            counts[no] += 1;
                          } else {
                            if (ch < 9449) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 9655) {
                          if (ch < 9654) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 9664) {
                            counts[so] += 1;
                          } else {
                            if (ch < 9665) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 10093) {
                      if (ch < 10088) {
                        if (ch < 9838) {
                          if (ch < 9727) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 9839) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 10087) {
                              counts[so] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10090) {
                          if (ch < 10089) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10091) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10092) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10098) {
                        if (ch < 10095) {
                          if (ch < 10094) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10096) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10097) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10100) {
                          if (ch < 10099) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10101) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10131) {
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
                if (ch < 10711) {
                  if (ch < 10629) {
                    if (ch < 10219) {
                      if (ch < 10214) {
                        if (ch < 10181) {
                          if (ch < 10180) {
                            counts[sm] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10182) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10213) {
                              counts[sm] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10216) {
                          if (ch < 10215) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10217) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10218) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10239) {
                        if (ch < 10221) {
                          if (ch < 10220) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10222) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10223) {
                              counts[pe] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10626) {
                          if (ch < 10495) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 10627) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10628) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 10639) {
                      if (ch < 10634) {
                        if (ch < 10631) {
                          if (ch < 10630) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10632) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10633) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10636) {
                          if (ch < 10635) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10637) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10638) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10644) {
                        if (ch < 10641) {
                          if (ch < 10640) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 10642) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10643) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10646) {
                          if (ch < 10645) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10647) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10648) {
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
                  if (ch < 11367) {
                    if (ch < 11076) {
                      if (ch < 10747) {
                        if (ch < 10713) {
                          if (ch < 10712) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 10714) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10715) {
                              counts[pe] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10749) {
                          if (ch < 10748) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 11007) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 11055) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11358) {
                        if (ch < 11084) {
                          if (ch < 11078) {
                            counts[so] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 11217) {
                            counts[so] += 1;
                          } else {
                            if (ch < 11310) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11361) {
                          if (ch < 11360) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11364) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11366) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11381) {
                      if (ch < 11372) {
                        if (ch < 11369) {
                          if (ch < 11368) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11370) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11371) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11377) {
                          if (ch < 11376) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11378) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11380) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11394) {
                        if (ch < 11389) {
                          if (ch < 11387) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 11392) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11393) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11396) {
                          if (ch < 11395) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11397) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11398) {
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
            if (ch < 12301) {
              if (ch < 11479) {
                if (ch < 11439) {
                  if (ch < 11419) {
                    if (ch < 11409) {
                      if (ch < 11404) {
                        if (ch < 11401) {
                          if (ch < 11400) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11402) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11403) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11406) {
                          if (ch < 11405) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11407) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11408) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11414) {
                        if (ch < 11411) {
                          if (ch < 11410) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11412) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11413) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11416) {
                          if (ch < 11415) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11417) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11418) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11429) {
                      if (ch < 11424) {
                        if (ch < 11421) {
                          if (ch < 11420) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11422) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11423) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11426) {
                          if (ch < 11425) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11427) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11428) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11434) {
                        if (ch < 11431) {
                          if (ch < 11430) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11432) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11433) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11436) {
                          if (ch < 11435) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11437) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11438) {
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
                  if (ch < 11459) {
                    if (ch < 11449) {
                      if (ch < 11444) {
                        if (ch < 11441) {
                          if (ch < 11440) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11442) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11443) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11446) {
                          if (ch < 11445) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11447) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11448) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11454) {
                        if (ch < 11451) {
                          if (ch < 11450) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11452) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11453) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11456) {
                          if (ch < 11455) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11457) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11458) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11469) {
                      if (ch < 11464) {
                        if (ch < 11461) {
                          if (ch < 11460) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11462) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11463) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11466) {
                          if (ch < 11465) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11467) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11468) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11474) {
                        if (ch < 11471) {
                          if (ch < 11470) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11472) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11473) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11476) {
                          if (ch < 11475) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11477) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11478) {
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
                if (ch < 11788) {
                  if (ch < 11507) {
                    if (ch < 11489) {
                      if (ch < 11484) {
                        if (ch < 11481) {
                          if (ch < 11480) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11482) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11483) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11486) {
                          if (ch < 11485) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 11487) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11488) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11500) {
                        if (ch < 11492) {
                          if (ch < 11490) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11498) {
                            counts[so] += 1;
                          } else {
                            if (ch < 11499) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11502) {
                          if (ch < 11501) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 11505) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 11506) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11775) {
                      if (ch < 11623) {
                        if (ch < 11517) {
                          if (ch < 11516) {
                            counts[po] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 11519) {
                            counts[po] += 1;
                          } else {
                            if (ch < 11565) {
                              counts[ll] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11632) {
                          if (ch < 11631) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 11647) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 11742) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11781) {
                        if (ch < 11778) {
                          if (ch < 11777) {
                            counts[po] += 1;
                          } else {
                            counts[pi] += 1;
                          }
                        } else {
                          if (ch < 11779) {
                            counts[pf] += 1;
                          } else {
                            if (ch < 11780) {
                              counts[pi] += 1;
                            } else {
                              counts[pf] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11785) {
                          if (ch < 11784) {
                            counts[po] += 1;
                          } else {
                            counts[pi] += 1;
                          }
                        } else {
                          if (ch < 11786) {
                            counts[pf] += 1;
                          } else {
                            if (ch < 11787) {
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
                  if (ch < 11822) {
                    if (ch < 11808) {
                      if (ch < 11802) {
                        if (ch < 11798) {
                          if (ch < 11789) {
                            counts[pf] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 11799) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 11801) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11804) {
                          if (ch < 11803) {
                            counts[po] += 1;
                          } else {
                            counts[pi] += 1;
                          }
                        } else {
                          if (ch < 11805) {
                            counts[pf] += 1;
                          } else {
                            if (ch < 11807) {
                              counts[po] += 1;
                            } else {
                              counts[pi] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11813) {
                        if (ch < 11810) {
                          if (ch < 11809) {
                            counts[pf] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 11811) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 11812) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11815) {
                          if (ch < 11814) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 11816) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 11817) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12291) {
                      if (ch < 11840) {
                        if (ch < 11833) {
                          if (ch < 11823) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 11835) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 11839) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11842) {
                          if (ch < 11841) {
                            counts[po] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 12283) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12288) {
                              counts[zs] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12296) {
                        if (ch < 12293) {
                          if (ch < 12292) {
                            counts[so] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 12294) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 12295) {
                              counts[nl] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12298) {
                          if (ch < 12297) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 12299) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 12300) {
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
              if (ch < 42569) {
                if (ch < 12693) {
                  if (ch < 12335) {
                    if (ch < 12312) {
                      if (ch < 12307) {
                        if (ch < 12303) {
                          if (ch < 12302) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 12304) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 12305) {
                              counts[pe] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12309) {
                          if (ch < 12308) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 12310) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 12311) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12317) {
                        if (ch < 12314) {
                          if (ch < 12313) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 12315) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 12316) {
                              counts[pd] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12320) {
                          if (ch < 12319) {
                            counts[pe] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 12329) {
                            counts[nl] += 1;
                          } else {
                            if (ch < 12333) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12442) {
                      if (ch < 12347) {
                        if (ch < 12341) {
                          if (ch < 12336) {
                            counts[pd] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 12343) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12346) {
                              counts[nl] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12349) {
                          if (ch < 12348) {
                            counts[lo] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 12351) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12438) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12538) {
                        if (ch < 12446) {
                          if (ch < 12444) {
                            counts[sk] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 12447) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 12448) {
                              counts[pd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12542) {
                          if (ch < 12539) {
                            counts[po] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 12686) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 12689) {
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
                  if (ch < 42124) {
                    if (ch < 12895) {
                      if (ch < 12830) {
                        if (ch < 12730) {
                          if (ch < 12703) {
                            counts[so] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 12771) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12799) {
                              counts[lo] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12871) {
                          if (ch < 12841) {
                            counts[no] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 12879) {
                            counts[no] += 1;
                          } else {
                            if (ch < 12880) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 13311) {
                        if (ch < 12937) {
                          if (ch < 12927) {
                            counts[so] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 12976) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12991) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 19967) {
                          if (ch < 19893) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 40980) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 40981) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42539) {
                      if (ch < 42507) {
                        if (ch < 42231) {
                          if (ch < 42182) {
                            counts[so] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 42237) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 42239) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42511) {
                          if (ch < 42508) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 42527) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 42537) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42564) {
                        if (ch < 42561) {
                          if (ch < 42560) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42562) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42563) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42566) {
                          if (ch < 42565) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42567) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42568) {
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
                if (ch < 42611) {
                  if (ch < 42589) {
                    if (ch < 42579) {
                      if (ch < 42574) {
                        if (ch < 42571) {
                          if (ch < 42570) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42572) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42573) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42576) {
                          if (ch < 42575) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42577) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42578) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42584) {
                        if (ch < 42581) {
                          if (ch < 42580) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42582) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42583) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42586) {
                          if (ch < 42585) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42587) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42588) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42599) {
                      if (ch < 42594) {
                        if (ch < 42591) {
                          if (ch < 42590) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42592) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42593) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42596) {
                          if (ch < 42595) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42597) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42598) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42604) {
                        if (ch < 42601) {
                          if (ch < 42600) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42602) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42603) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42606) {
                          if (ch < 42605) {
                            counts[ll] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 42607) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 42610) {
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
                  if (ch < 42640) {
                    if (ch < 42630) {
                      if (ch < 42625) {
                        if (ch < 42622) {
                          if (ch < 42621) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 42623) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 42624) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42627) {
                          if (ch < 42626) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42628) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42629) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42635) {
                        if (ch < 42632) {
                          if (ch < 42631) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42633) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42634) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42637) {
                          if (ch < 42636) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42638) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42639) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42650) {
                      if (ch < 42645) {
                        if (ch < 42642) {
                          if (ch < 42641) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42643) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42644) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42647) {
                          if (ch < 42646) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42648) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42649) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42735) {
                        if (ch < 42653) {
                          if (ch < 42651) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 42655) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 42725) {
                              counts[lo] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42743) {
                          if (ch < 42737) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 42774) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 42783) {
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
          if (ch < 65341) {
            if (ch < 43347) {
              if (ch < 42874) {
                if (ch < 42827) {
                  if (ch < 42807) {
                    if (ch < 42795) {
                      if (ch < 42790) {
                        if (ch < 42787) {
                          if (ch < 42786) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42788) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42789) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42792) {
                          if (ch < 42791) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42793) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42794) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42802) {
                        if (ch < 42797) {
                          if (ch < 42796) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42798) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42801) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42804) {
                          if (ch < 42803) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42805) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42806) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42817) {
                      if (ch < 42812) {
                        if (ch < 42809) {
                          if (ch < 42808) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42810) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42811) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42814) {
                          if (ch < 42813) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42815) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42816) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42822) {
                        if (ch < 42819) {
                          if (ch < 42818) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42820) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42821) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42824) {
                          if (ch < 42823) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42825) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42826) {
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
                  if (ch < 42847) {
                    if (ch < 42837) {
                      if (ch < 42832) {
                        if (ch < 42829) {
                          if (ch < 42828) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42830) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42831) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42834) {
                          if (ch < 42833) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42835) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42836) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42842) {
                        if (ch < 42839) {
                          if (ch < 42838) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42840) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42841) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42844) {
                          if (ch < 42843) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42845) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42846) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42857) {
                      if (ch < 42852) {
                        if (ch < 42849) {
                          if (ch < 42848) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42850) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42851) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42854) {
                          if (ch < 42853) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42855) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42856) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42862) {
                        if (ch < 42859) {
                          if (ch < 42858) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42860) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42861) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42864) {
                          if (ch < 42863) {
                            counts[ll] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 42872) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42873) {
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
                if (ch < 42919) {
                  if (ch < 42897) {
                    if (ch < 42885) {
                      if (ch < 42880) {
                        if (ch < 42876) {
                          if (ch < 42875) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42878) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42879) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42882) {
                          if (ch < 42881) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42883) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42884) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42891) {
                        if (ch < 42887) {
                          if (ch < 42886) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42888) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 42890) {
                              counts[sk] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42893) {
                          if (ch < 42892) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42894) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42896) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42909) {
                      if (ch < 42904) {
                        if (ch < 42901) {
                          if (ch < 42898) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42902) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42903) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42906) {
                          if (ch < 42905) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42907) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42908) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42914) {
                        if (ch < 42911) {
                          if (ch < 42910) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42912) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42913) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42916) {
                          if (ch < 42915) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 42917) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42918) {
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
                  if (ch < 43064) {
                    if (ch < 43014) {
                      if (ch < 43001) {
                        if (ch < 42921) {
                          if (ch < 42920) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 42929) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42999) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43009) {
                          if (ch < 43002) {
                            counts[ll] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43010) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43013) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43046) {
                        if (ch < 43019) {
                          if (ch < 43018) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43042) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43044) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43051) {
                          if (ch < 43047) {
                            counts[mc] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 43061) {
                            counts[no] += 1;
                          } else {
                            if (ch < 43063) {
                              counts[so] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43249) {
                      if (ch < 43187) {
                        if (ch < 43123) {
                          if (ch < 43065) {
                            counts[so] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43127) {
                            counts[po] += 1;
                          } else {
                            if (ch < 43137) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43204) {
                          if (ch < 43203) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43215) {
                            counts[po] += 1;
                          } else {
                            if (ch < 43225) {
                              counts[nd] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43301) {
                        if (ch < 43258) {
                          if (ch < 43255) {
                            counts[lo] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 43259) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43273) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43311) {
                          if (ch < 43309) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 43334) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43345) {
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
              if (ch < 57343) {
                if (ch < 43644) {
                  if (ch < 43513) {
                    if (ch < 43452) {
                      if (ch < 43442) {
                        if (ch < 43388) {
                          if (ch < 43359) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43394) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43395) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43445) {
                          if (ch < 43443) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 43449) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43451) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43487) {
                        if (ch < 43469) {
                          if (ch < 43456) {
                            counts[mc] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 43471) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 43481) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43493) {
                          if (ch < 43492) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43494) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 43503) {
                              counts[lo] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43596) {
                      if (ch < 43572) {
                        if (ch < 43566) {
                          if (ch < 43560) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43568) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 43570) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43586) {
                          if (ch < 43574) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43587) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43595) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43632) {
                        if (ch < 43609) {
                          if (ch < 43597) {
                            counts[mc] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 43615) {
                            counts[po] += 1;
                          } else {
                            if (ch < 43631) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43641) {
                          if (ch < 43638) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 43642) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43643) {
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
                  if (ch < 43762) {
                    if (ch < 43712) {
                      if (ch < 43700) {
                        if (ch < 43695) {
                          if (ch < 43645) {
                            counts[mc] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43696) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43697) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43704) {
                          if (ch < 43702) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43709) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43711) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43754) {
                        if (ch < 43740) {
                          if (ch < 43713) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 43741) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 43743) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43757) {
                          if (ch < 43755) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 43759) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 43761) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 44004) {
                      if (ch < 43866) {
                        if (ch < 43765) {
                          if (ch < 43764) {
                            counts[lm] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 43766) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43822) {
                              counts[lo] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43871) {
                          if (ch < 43867) {
                            counts[sk] += 1;
                          } else {
                            counts[lm] += 1;
                          }
                        } else {
                          if (ch < 43877) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 44002) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 44011) {
                        if (ch < 44007) {
                          if (ch < 44005) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 44008) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 44010) {
                              counts[mc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 44013) {
                          if (ch < 44012) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 44025) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 55291) {
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
                if (ch < 65092) {
                  if (ch < 65049) {
                    if (ch < 64829) {
                      if (ch < 64286) {
                        if (ch < 64217) {
                          if (ch < 63743) {
                            counts[co] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 64279) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 64285) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 64297) {
                          if (ch < 64296) {
                            counts[lo] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 64433) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 64449) {
                              counts[sk] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65021) {
                        if (ch < 64831) {
                          if (ch < 64830) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65019) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 65020) {
                              counts[sc] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65046) {
                          if (ch < 65039) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 65047) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65048) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65082) {
                      if (ch < 65077) {
                        if (ch < 65072) {
                          if (ch < 65069) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 65074) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 65076) {
                              counts[pc] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65079) {
                          if (ch < 65078) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65080) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65081) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65087) {
                        if (ch < 65084) {
                          if (ch < 65083) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 65085) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65086) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65089) {
                          if (ch < 65088) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65090) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65091) {
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
                  if (ch < 65131) {
                    if (ch < 65115) {
                      if (ch < 65103) {
                        if (ch < 65095) {
                          if (ch < 65094) {
                            counts[po] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65096) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65100) {
                              counts[po] += 1;
                            } else {
                              counts[pc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65112) {
                          if (ch < 65111) {
                            counts[po] += 1;
                          } else {
                            counts[pd] += 1;
                          }
                        } else {
                          if (ch < 65113) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65114) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65122) {
                        if (ch < 65117) {
                          if (ch < 65116) {
                            counts[pe] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65118) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65121) {
                              counts[po] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65126) {
                          if (ch < 65123) {
                            counts[pd] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 65128) {
                            counts[po] += 1;
                          } else {
                            if (ch < 65129) {
                              counts[sc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65292) {
                      if (ch < 65287) {
                        if (ch < 65279) {
                          if (ch < 65276) {
                            counts[lo] += 1;
                          } else {
                            counts[cf] += 1;
                          }
                        } else {
                          if (ch < 65283) {
                            counts[po] += 1;
                          } else {
                            if (ch < 65284) {
                              counts[sc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65289) {
                          if (ch < 65288) {
                            counts[ps] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 65290) {
                            counts[po] += 1;
                          } else {
                            if (ch < 65291) {
                              counts[sm] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65310) {
                        if (ch < 65295) {
                          if (ch < 65293) {
                            counts[pd] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 65305) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 65307) {
                              counts[po] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65338) {
                          if (ch < 65312) {
                            counts[po] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 65339) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65340) {
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
            if (ch < 70457) {
              if (ch < 68184) {
                if (ch < 66256) {
                  if (ch < 65505) {
                    if (ch < 65376) {
                      if (ch < 65371) {
                        if (ch < 65343) {
                          if (ch < 65342) {
                            counts[sk] += 1;
                          } else {
                            counts[pc] += 1;
                          }
                        } else {
                          if (ch < 65344) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 65370) {
                              counts[ll] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65373) {
                          if (ch < 65372) {
                            counts[sm] += 1;
                          } else {
                            counts[pe] += 1;
                          }
                        } else {
                          if (ch < 65374) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 65375) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65391) {
                        if (ch < 65378) {
                          if (ch < 65377) {
                            counts[po] += 1;
                          } else {
                            counts[ps] += 1;
                          }
                        } else {
                          if (ch < 65379) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65381) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65437) {
                          if (ch < 65392) {
                            counts[lm] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 65439) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 65500) {
                              counts[lo] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65786) {
                      if (ch < 65512) {
                        if (ch < 65507) {
                          if (ch < 65506) {
                            counts[sm] += 1;
                          } else {
                            counts[sk] += 1;
                          }
                        } else {
                          if (ch < 65508) {
                            counts[so] += 1;
                          } else {
                            if (ch < 65510) {
                              counts[sc] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65518) {
                          if (ch < 65516) {
                            counts[sm] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 65531) {
                            counts[cf] += 1;
                          } else {
                            if (ch < 65533) {
                              counts[so] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65912) {
                        if (ch < 65843) {
                          if (ch < 65794) {
                            counts[po] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 65855) {
                            counts[so] += 1;
                          } else {
                            if (ch < 65908) {
                              counts[nl] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65931) {
                          if (ch < 65929) {
                            counts[so] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 66044) {
                            counts[so] += 1;
                          } else {
                            if (ch < 66045) {
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
                  if (ch < 66915) {
                    if (ch < 66426) {
                      if (ch < 66368) {
                        if (ch < 66299) {
                          if (ch < 66272) {
                            counts[mn] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 66335) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 66339) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 66377) {
                          if (ch < 66369) {
                            counts[nl] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 66378) {
                            counts[nl] += 1;
                          } else {
                            if (ch < 66421) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 66517) {
                        if (ch < 66463) {
                          if (ch < 66461) {
                            counts[lo] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 66511) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 66512) {
                              counts[po] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 66639) {
                          if (ch < 66599) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 66717) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 66729) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 67861) {
                      if (ch < 67702) {
                        if (ch < 67669) {
                          if (ch < 66927) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 67671) {
                            counts[po] += 1;
                          } else {
                            if (ch < 67679) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 67711) {
                          if (ch < 67704) {
                            counts[so] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 67742) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 67759) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 68096) {
                        if (ch < 67871) {
                          if (ch < 67867) {
                            counts[no] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 67897) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 67903) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68147) {
                          if (ch < 68111) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 68159) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 68167) {
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
                if (ch < 69825) {
                  if (ch < 68527) {
                    if (ch < 68335) {
                      if (ch < 68255) {
                        if (ch < 68222) {
                          if (ch < 68220) {
                            counts[lo] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 68223) {
                            counts[po] += 1;
                          } else {
                            if (ch < 68252) {
                              counts[lo] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68296) {
                          if (ch < 68295) {
                            counts[lo] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 68324) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 68326) {
                              counts[mn] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 68447) {
                        if (ch < 68405) {
                          if (ch < 68342) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 68415) {
                            counts[po] += 1;
                          } else {
                            if (ch < 68437) {
                              counts[lo] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68479) {
                          if (ch < 68466) {
                            counts[lo] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 68497) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 68508) {
                              counts[po] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 69743) {
                      if (ch < 69634) {
                        if (ch < 69246) {
                          if (ch < 68680) {
                            counts[lo] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 69632) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 69633) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 69702) {
                          if (ch < 69687) {
                            counts[lo] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 69709) {
                            counts[po] += 1;
                          } else {
                            if (ch < 69733) {
                              counts[no] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 69814) {
                        if (ch < 69762) {
                          if (ch < 69761) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 69807) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 69810) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 69818) {
                          if (ch < 69816) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 69820) {
                            counts[po] += 1;
                          } else {
                            if (ch < 69821) {
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
                  if (ch < 70084) {
                    if (ch < 70002) {
                      if (ch < 69931) {
                        if (ch < 69881) {
                          if (ch < 69864) {
                            counts[lo] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 69890) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 69926) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 69940) {
                          if (ch < 69932) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 69951) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 69955) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70018) {
                        if (ch < 70005) {
                          if (ch < 70003) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 70006) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70017) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70069) {
                          if (ch < 70066) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 70078) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70080) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70197) {
                      if (ch < 70187) {
                        if (ch < 70105) {
                          if (ch < 70093) {
                            counts[po] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 70106) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70132) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70193) {
                          if (ch < 70190) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 70195) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 70196) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70370) {
                        if (ch < 70205) {
                          if (ch < 70199) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 70366) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70367) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70393) {
                          if (ch < 70378) {
                            counts[mn] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 70401) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70403) {
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
              if (ch < 119140) {
                if (ch < 71338) {
                  if (ch < 70855) {
                    if (ch < 70834) {
                      if (ch < 70487) {
                        if (ch < 70461) {
                          if (ch < 70460) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 70463) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 70464) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70499) {
                          if (ch < 70497) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 70516) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70831) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70848) {
                        if (ch < 70841) {
                          if (ch < 70840) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 70842) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70846) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70851) {
                          if (ch < 70849) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 70853) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70854) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 71215) {
                      if (ch < 71099) {
                        if (ch < 71086) {
                          if (ch < 70873) {
                            counts[nd] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 71089) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 71093) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71102) {
                          if (ch < 71101) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 71104) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 71113) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 71230) {
                        if (ch < 71226) {
                          if (ch < 71218) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 71228) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 71229) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71235) {
                          if (ch < 71232) {
                            counts[mn] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 71236) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 71257) {
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
                  if (ch < 92916) {
                    if (ch < 71903) {
                      if (ch < 71349) {
                        if (ch < 71340) {
                          if (ch < 71339) {
                            counts[mn] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 71341) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 71343) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71351) {
                          if (ch < 71350) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 71369) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 71871) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 74868) {
                        if (ch < 71922) {
                          if (ch < 71913) {
                            counts[nd] += 1;
                          } else {
                            counts[no] += 1;
                          }
                        } else {
                          if (ch < 74648) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 74862) {
                              counts[nl] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 92777) {
                          if (ch < 92766) {
                            counts[lo] += 1;
                          } else {
                            counts[nd] += 1;
                          }
                        } else {
                          if (ch < 92783) {
                            counts[po] += 1;
                          } else {
                            if (ch < 92909) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 93025) {
                      if (ch < 92991) {
                        if (ch < 92975) {
                          if (ch < 92917) {
                            counts[po] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 92982) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 92987) {
                              counts[po] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 92996) {
                          if (ch < 92995) {
                            counts[lm] += 1;
                          } else {
                            counts[po] += 1;
                          }
                        } else {
                          if (ch < 92997) {
                            counts[so] += 1;
                          } else {
                            if (ch < 93017) {
                              counts[nd] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 113817) {
                        if (ch < 94078) {
                          if (ch < 94032) {
                            counts[lo] += 1;
                          } else {
                            counts[mc] += 1;
                          }
                        } else {
                          if (ch < 94098) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 94111) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 113822) {
                          if (ch < 113820) {
                            counts[so] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 113823) {
                            counts[po] += 1;
                          } else {
                            if (ch < 113827) {
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
                if (ch < 120485) {
                  if (ch < 119963) {
                    if (ch < 119213) {
                      if (ch < 119162) {
                        if (ch < 119145) {
                          if (ch < 119142) {
                            counts[mc] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 119148) {
                            counts[so] += 1;
                          } else {
                            if (ch < 119154) {
                              counts[mc] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 119172) {
                          if (ch < 119170) {
                            counts[mn] += 1;
                          } else {
                            counts[so] += 1;
                          }
                        } else {
                          if (ch < 119179) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 119209) {
                              counts[so] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 119833) {
                        if (ch < 119364) {
                          if (ch < 119361) {
                            counts[so] += 1;
                          } else {
                            counts[mn] += 1;
                          }
                        } else {
                          if (ch < 119638) {
                            counts[so] += 1;
                          } else {
                            if (ch < 119665) {
                              counts[no] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 119885) {
                          if (ch < 119859) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 119911) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 119937) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 120223) {
                      if (ch < 120092) {
                        if (ch < 120015) {
                          if (ch < 119989) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 120041) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120067) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120144) {
                          if (ch < 120119) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 120171) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120197) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 120353) {
                        if (ch < 120275) {
                          if (ch < 120249) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 120301) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120327) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120405) {
                          if (ch < 120379) {
                            counts[ll] += 1;
                          } else {
                            counts[lu] += 1;
                          }
                        } else {
                          if (ch < 120431) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120457) {
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
                  if (ch < 120719) {
                    if (ch < 120603) {
                      if (ch < 120545) {
                        if (ch < 120513) {
                          if (ch < 120512) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120538) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120539) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120571) {
                          if (ch < 120570) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120596) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120597) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 120661) {
                        if (ch < 120629) {
                          if (ch < 120628) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120654) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120655) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120687) {
                          if (ch < 120686) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120712) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120713) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 125135) {
                      if (ch < 120777) {
                        if (ch < 120745) {
                          if (ch < 120744) {
                            counts[lu] += 1;
                          } else {
                            counts[sm] += 1;
                          }
                        } else {
                          if (ch < 120770) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120771) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120779) {
                          if (ch < 120778) {
                            counts[lu] += 1;
                          } else {
                            counts[ll] += 1;
                          }
                        } else {
                          if (ch < 120831) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 125124) {
                              counts[lo] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 127244) {
                        if (ch < 126651) {
                          if (ch < 125142) {
                            counts[mn] += 1;
                          } else {
                            counts[lo] += 1;
                          }
                        } else {
                          if (ch < 126705) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 127221) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 917631) {
                          if (ch < 129197) {
                            counts[so] += 1;
                          } else {
                            if (ch < 195101) {
                              counts[lo] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        } else {
                          if (ch < 917999) {
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
    printf("%lu\t%s\n", ascii_cnt, "ASCII");
  for (i = 0; i < 30; ++i) {
    if (counts[i] > 0) {
      if (long_names)
        printf("%lu\t\%s\n", counts[i], long_categories[i]);
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
