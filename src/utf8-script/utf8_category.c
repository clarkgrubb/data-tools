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
      if (ch < 8218) {
        if (ch < 2946) {
          if (ch < 1164) {
            if (ch < 474) {
              if (ch < 335) {
                if (ch < 278) {
                  if (ch < 215) {
                    if (ch < 175) {
                      if (ch < 168) {
                        if (ch < 162) {
                          if (ch < 160) {
                            counts[cc] += 1;
                          } else {
                            if (ch < 161) {
                              counts[zs] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 166) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 167) {
                              counts[so] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 171) {
                          if (ch < 169) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 170) {
                              counts[so] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 173) {
                            if (ch < 172) {
                              counts[pi] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          } else {
                            if (ch < 174) {
                              counts[cf] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 184) {
                        if (ch < 178) {
                          if (ch < 176) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 177) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        } else {
                          if (ch < 181) {
                            if (ch < 180) {
                              counts[no] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          } else {
                            if (ch < 182) {
                              counts[ll] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 187) {
                          if (ch < 185) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 186) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 191) {
                            if (ch < 188) {
                              counts[pf] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          } else {
                            if (ch < 192) {
                              counts[po] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 264) {
                      if (ch < 257) {
                        if (ch < 247) {
                          if (ch < 216) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 223) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 248) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 256) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 260) {
                          if (ch < 258) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 259) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 262) {
                            if (ch < 261) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 263) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 271) {
                        if (ch < 267) {
                          if (ch < 265) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 266) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 269) {
                            if (ch < 268) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 270) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 274) {
                          if (ch < 272) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 273) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 305) {
                    if (ch < 291) {
                      if (ch < 284) {
                        if (ch < 281) {
                          if (ch < 279) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 280) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
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
                      } else {
                        if (ch < 287) {
                          if (ch < 285) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 286) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 289) {
                            if (ch < 288) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 290) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 298) {
                        if (ch < 294) {
                          if (ch < 292) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 293) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 301) {
                          if (ch < 299) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 300) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 303) {
                            if (ch < 302) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 304) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 320) {
                      if (ch < 313) {
                        if (ch < 308) {
                          if (ch < 306) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 307) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 310) {
                            if (ch < 309) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 311) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 316) {
                          if (ch < 314) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 315) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 318) {
                            if (ch < 317) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 319) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 327) {
                        if (ch < 323) {
                          if (ch < 321) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 322) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 325) {
                            if (ch < 324) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 326) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 331) {
                          if (ch < 328) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 330) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 396) {
                  if (ch < 362) {
                    if (ch < 348) {
                      if (ch < 341) {
                        if (ch < 338) {
                          if (ch < 336) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 337) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
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
                        if (ch < 344) {
                          if (ch < 342) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 343) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 346) {
                            if (ch < 345) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 347) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 355) {
                        if (ch < 351) {
                          if (ch < 349) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 350) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 358) {
                          if (ch < 356) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 357) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 360) {
                            if (ch < 359) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 361) {
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
                      if (ch < 368) {
                        if (ch < 365) {
                          if (ch < 363) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 364) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 366) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 367) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 371) {
                          if (ch < 369) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 370) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 385) {
                        if (ch < 379) {
                          if (ch < 376) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 378) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 381) {
                            if (ch < 380) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 382) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 389) {
                          if (ch < 387) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 388) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 392) {
                            if (ch < 390) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 393) {
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
                  if (ch < 439) {
                    if (ch < 420) {
                      if (ch < 409) {
                        if (ch < 403) {
                          if (ch < 398) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 402) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 405) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 406) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 415) {
                          if (ch < 412) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 414) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 418) {
                            if (ch < 417) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 419) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 429) {
                        if (ch < 424) {
                          if (ch < 421) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 422) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 426) {
                            if (ch < 425) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 428) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 433) {
                          if (ch < 430) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 432) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 437) {
                            if (ch < 436) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 438) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 460) {
                      if (ch < 453) {
                        if (ch < 444) {
                          if (ch < 441) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 443) {
                              counts[ll] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 448) {
                            if (ch < 445) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 452) {
                              counts[lo] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 456) {
                          if (ch < 454) {
                            counts[lt] += 1;
                          } else {
                            if (ch < 455) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
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
                              counts[lt] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 467) {
                        if (ch < 463) {
                          if (ch < 461) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 462) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 465) {
                            if (ch < 464) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 466) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 470) {
                          if (ch < 468) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 469) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 472) {
                            if (ch < 471) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 473) {
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
              if (ch < 741) {
                if (ch < 532) {
                  if (ch < 505) {
                    if (ch < 488) {
                      if (ch < 481) {
                        if (ch < 478) {
                          if (ch < 475) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 476) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 479) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 480) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 484) {
                          if (ch < 482) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 483) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 486) {
                            if (ch < 485) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 487) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 495) {
                        if (ch < 491) {
                          if (ch < 489) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 490) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 493) {
                            if (ch < 492) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 494) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 499) {
                          if (ch < 497) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 498) {
                              counts[lu] += 1;
                            } else {
                              counts[lt] += 1;
                            }
                          }
                        } else {
                          if (ch < 501) {
                            if (ch < 500) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 502) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 518) {
                      if (ch < 511) {
                        if (ch < 508) {
                          if (ch < 506) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 507) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 509) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 510) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 514) {
                          if (ch < 512) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 513) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 516) {
                            if (ch < 515) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 517) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 525) {
                        if (ch < 521) {
                          if (ch < 519) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 520) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 523) {
                            if (ch < 522) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 524) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 528) {
                          if (ch < 526) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 527) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 530) {
                            if (ch < 529) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 531) {
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
                    if (ch < 545) {
                      if (ch < 538) {
                        if (ch < 535) {
                          if (ch < 533) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 534) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 536) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 537) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 541) {
                          if (ch < 539) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 540) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 543) {
                            if (ch < 542) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 544) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 552) {
                        if (ch < 548) {
                          if (ch < 546) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 547) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 550) {
                            if (ch < 549) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 551) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 555) {
                          if (ch < 553) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 554) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 585) {
                      if (ch < 573) {
                        if (ch < 562) {
                          if (ch < 560) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 561) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 570) {
                            if (ch < 563) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 572) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 578) {
                          if (ch < 575) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 577) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 583) {
                            if (ch < 579) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 584) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 660) {
                        if (ch < 588) {
                          if (ch < 586) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 587) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 590) {
                            if (ch < 589) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 591) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 706) {
                          if (ch < 661) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 688) {
                              counts[ll] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 722) {
                            if (ch < 710) {
                              counts[sk] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          } else {
                            if (ch < 736) {
                              counts[sk] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 1001) {
                  if (ch < 910) {
                    if (ch < 887) {
                      if (ch < 880) {
                        if (ch < 750) {
                          if (ch < 748) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 749) {
                              counts[lm] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        } else {
                          if (ch < 751) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 768) {
                              counts[sk] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 883) {
                          if (ch < 881) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 882) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 885) {
                            if (ch < 884) {
                              counts[ll] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          } else {
                            if (ch < 886) {
                              counts[sk] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 900) {
                        if (ch < 891) {
                          if (ch < 888) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 890) {
                              counts[unknown] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 895) {
                            if (ch < 894) {
                              counts[ll] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 896) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 904) {
                          if (ch < 902) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 903) {
                              counts[lu] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 908) {
                            if (ch < 907) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 909) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 987) {
                      if (ch < 975) {
                        if (ch < 930) {
                          if (ch < 912) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 913) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 931) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 940) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 981) {
                          if (ch < 976) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 978) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 994) {
                        if (ch < 990) {
                          if (ch < 988) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 989) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 992) {
                            if (ch < 991) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 993) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 997) {
                          if (ch < 995) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 996) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 999) {
                            if (ch < 998) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1000) {
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
                  if (ch < 1131) {
                    if (ch < 1019) {
                      if (ch < 1007) {
                        if (ch < 1004) {
                          if (ch < 1002) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1003) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1005) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1006) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1014) {
                          if (ch < 1012) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1013) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1016) {
                            if (ch < 1015) {
                              counts[sm] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1017) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1124) {
                        if (ch < 1120) {
                          if (ch < 1021) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1072) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1122) {
                            if (ch < 1121) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1123) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1127) {
                          if (ch < 1125) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1126) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1129) {
                            if (ch < 1128) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
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
                  } else {
                    if (ch < 1145) {
                      if (ch < 1138) {
                        if (ch < 1134) {
                          if (ch < 1132) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1133) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1136) {
                            if (ch < 1135) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1137) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1141) {
                          if (ch < 1139) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1140) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1152) {
                        if (ch < 1148) {
                          if (ch < 1146) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1147) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1150) {
                            if (ch < 1149) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1151) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1155) {
                          if (ch < 1153) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1154) {
                              counts[ll] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 1162) {
                            if (ch < 1160) {
                              counts[mn] += 1;
                            } else {
                              counts[me] += 1;
                            }
                          } else {
                            if (ch < 1163) {
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
            if (ch < 1767) {
              if (ch < 1275) {
                if (ch < 1219) {
                  if (ch < 1191) {
                    if (ch < 1177) {
                      if (ch < 1170) {
                        if (ch < 1167) {
                          if (ch < 1165) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1166) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1168) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1169) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1173) {
                          if (ch < 1171) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1172) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1175) {
                            if (ch < 1174) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1176) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1184) {
                        if (ch < 1180) {
                          if (ch < 1178) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1179) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1182) {
                            if (ch < 1181) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1183) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1187) {
                          if (ch < 1185) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1186) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1189) {
                            if (ch < 1188) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1190) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1204) {
                      if (ch < 1197) {
                        if (ch < 1194) {
                          if (ch < 1192) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1193) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1195) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1196) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1200) {
                          if (ch < 1198) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1199) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1202) {
                            if (ch < 1201) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1203) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1211) {
                        if (ch < 1207) {
                          if (ch < 1205) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1206) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1209) {
                            if (ch < 1208) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1210) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1214) {
                          if (ch < 1212) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1213) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1216) {
                            if (ch < 1215) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1218) {
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
                  if (ch < 1247) {
                    if (ch < 1233) {
                      if (ch < 1225) {
                        if (ch < 1222) {
                          if (ch < 1220) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1221) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1223) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1224) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1228) {
                          if (ch < 1226) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1227) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1230) {
                            if (ch < 1229) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1232) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1240) {
                        if (ch < 1236) {
                          if (ch < 1234) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1235) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1238) {
                            if (ch < 1237) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1239) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1243) {
                          if (ch < 1241) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1242) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1261) {
                      if (ch < 1254) {
                        if (ch < 1250) {
                          if (ch < 1248) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1249) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1252) {
                            if (ch < 1251) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1253) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1257) {
                          if (ch < 1255) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1256) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1259) {
                            if (ch < 1258) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1260) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1268) {
                        if (ch < 1264) {
                          if (ch < 1262) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1263) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1266) {
                            if (ch < 1265) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 1267) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1271) {
                          if (ch < 1269) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1270) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1273) {
                            if (ch < 1272) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1274) {
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
                if (ch < 1329) {
                  if (ch < 1302) {
                    if (ch < 1288) {
                      if (ch < 1281) {
                        if (ch < 1278) {
                          if (ch < 1276) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1277) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1279) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1280) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1284) {
                          if (ch < 1282) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1283) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 1286) {
                            if (ch < 1285) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
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
                      if (ch < 1295) {
                        if (ch < 1291) {
                          if (ch < 1289) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1290) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1293) {
                            if (ch < 1292) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1294) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1298) {
                          if (ch < 1296) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1297) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1315) {
                      if (ch < 1308) {
                        if (ch < 1305) {
                          if (ch < 1303) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1304) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
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
                      } else {
                        if (ch < 1311) {
                          if (ch < 1309) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1310) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1313) {
                            if (ch < 1312) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1314) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1322) {
                        if (ch < 1318) {
                          if (ch < 1316) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 1317) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1325) {
                          if (ch < 1323) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1324) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 1327) {
                            if (ch < 1326) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 1328) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 1525) {
                    if (ch < 1425) {
                      if (ch < 1416) {
                        if (ch < 1370) {
                          if (ch < 1367) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 1369) {
                              counts[unknown] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 1376) {
                            counts[po] += 1;
                          } else {
                            if (ch < 1377) {
                              counts[unknown] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1419) {
                          if (ch < 1417) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 1418) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        } else {
                          if (ch < 1423) {
                            if (ch < 1421) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 1424) {
                              counts[sc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1478) {
                        if (ch < 1472) {
                          if (ch < 1470) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1471) {
                              counts[pd] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 1475) {
                            if (ch < 1473) {
                              counts[po] += 1;
                            } else {
                              counts[mn] += 1;
                            }
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
                            if (ch < 1480) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 1520) {
                            if (ch < 1515) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 1523) {
                              counts[lo] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1601) {
                      if (ch < 1552) {
                        if (ch < 1545) {
                          if (ch < 1536) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 1542) {
                              counts[cf] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        } else {
                          if (ch < 1548) {
                            if (ch < 1547) {
                              counts[po] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          } else {
                            if (ch < 1550) {
                              counts[po] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1565) {
                          if (ch < 1563) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1564) {
                              counts[po] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        } else {
                          if (ch < 1568) {
                            if (ch < 1566) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 1600) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1748) {
                        if (ch < 1642) {
                          if (ch < 1611) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1632) {
                              counts[mn] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        } else {
                          if (ch < 1648) {
                            if (ch < 1646) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 1649) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1757) {
                          if (ch < 1749) {
                            counts[po] += 1;
                          } else {
                            if (ch < 1750) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 1759) {
                            if (ch < 1758) {
                              counts[cf] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 1765) {
                              counts[mn] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 2564) {
                if (ch < 2369) {
                  if (ch < 2043) {
                    if (ch < 1810) {
                      if (ch < 1789) {
                        if (ch < 1774) {
                          if (ch < 1769) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 1770) {
                              counts[so] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 1776) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1786) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1806) {
                          if (ch < 1791) {
                            counts[so] += 1;
                          } else {
                            if (ch < 1792) {
                              counts[lo] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 1808) {
                            if (ch < 1807) {
                              counts[unknown] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          } else {
                            if (ch < 1809) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 1984) {
                        if (ch < 1869) {
                          if (ch < 1840) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 1867) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 1969) {
                            if (ch < 1958) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 1970) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2036) {
                          if (ch < 1994) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 2027) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
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
                              counts[lm] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2137) {
                      if (ch < 2085) {
                        if (ch < 2074) {
                          if (ch < 2048) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2070) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2075) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 2084) {
                              counts[mn] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2094) {
                          if (ch < 2088) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2089) {
                              counts[lm] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2111) {
                            if (ch < 2096) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 2112) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2307) {
                        if (ch < 2143) {
                          if (ch < 2140) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2142) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 2227) {
                            if (ch < 2208) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 2276) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2363) {
                          if (ch < 2308) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2362) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2365) {
                            if (ch < 2364) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
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
                  if (ch < 2490) {
                    if (ch < 2433) {
                      if (ch < 2392) {
                        if (ch < 2382) {
                          if (ch < 2377) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2381) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2384) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2385) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2406) {
                          if (ch < 2402) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2404) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 2417) {
                            if (ch < 2416) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 2418) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2451) {
                        if (ch < 2437) {
                          if (ch < 2434) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2436) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2447) {
                            if (ch < 2445) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2449) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2481) {
                          if (ch < 2473) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2474) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 2483) {
                            if (ch < 2482) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 2486) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2524) {
                      if (ch < 2505) {
                        if (ch < 2494) {
                          if (ch < 2492) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2493) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 2501) {
                            if (ch < 2497) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 2503) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2510) {
                          if (ch < 2507) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2509) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2519) {
                            if (ch < 2511) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2520) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2546) {
                        if (ch < 2530) {
                          if (ch < 2526) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2527) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 2534) {
                            if (ch < 2532) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2544) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2555) {
                          if (ch < 2548) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 2554) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 2561) {
                            if (ch < 2556) {
                              counts[sc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2563) {
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
                if (ch < 2759) {
                  if (ch < 2653) {
                    if (ch < 2616) {
                      if (ch < 2601) {
                        if (ch < 2575) {
                          if (ch < 2565) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2571) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2577) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2579) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2610) {
                          if (ch < 2602) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2609) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2613) {
                            if (ch < 2612) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2615) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2631) {
                        if (ch < 2621) {
                          if (ch < 2618) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2620) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2625) {
                            if (ch < 2622) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 2627) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2638) {
                          if (ch < 2633) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2635) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2642) {
                            if (ch < 2641) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 2649) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2706) {
                      if (ch < 2678) {
                        if (ch < 2662) {
                          if (ch < 2654) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2655) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2674) {
                            if (ch < 2672) {
                              counts[nd] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 2677) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2692) {
                          if (ch < 2689) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2691) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 2702) {
                            if (ch < 2693) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 2703) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2741) {
                        if (ch < 2730) {
                          if (ch < 2707) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2729) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2738) {
                            if (ch < 2737) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2740) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2749) {
                          if (ch < 2746) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2748) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2753) {
                            if (ch < 2750) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 2758) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2868) {
                    if (ch < 2801) {
                      if (ch < 2768) {
                        if (ch < 2763) {
                          if (ch < 2761) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2762) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2765) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2766) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2786) {
                          if (ch < 2769) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2784) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 2790) {
                            if (ch < 2788) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2800) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2831) {
                        if (ch < 2818) {
                          if (ch < 2802) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 2817) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 2821) {
                            if (ch < 2820) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2829) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2857) {
                          if (ch < 2833) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2835) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 2865) {
                            if (ch < 2858) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 2866) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2894) {
                      if (ch < 2880) {
                        if (ch < 2876) {
                          if (ch < 2869) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2874) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2878) {
                            if (ch < 2877) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 2879) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2887) {
                          if (ch < 2881) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 2885) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2891) {
                            if (ch < 2889) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2893) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 2914) {
                        if (ch < 2904) {
                          if (ch < 2902) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2903) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 2910) {
                            if (ch < 2908) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 2911) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2928) {
                          if (ch < 2916) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2918) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        } else {
                          if (ch < 2930) {
                            if (ch < 2929) {
                              counts[so] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 2936) {
                              counts[no] += 1;
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
          if (ch < 6593) {
            if (ch < 3844) {
              if (ch < 3332) {
                if (ch < 3141) {
                  if (ch < 3018) {
                    if (ch < 2974) {
                      if (ch < 2961) {
                        if (ch < 2949) {
                          if (ch < 2947) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 2948) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2955) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2958) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 2969) {
                          if (ch < 2962) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 2966) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 2972) {
                            if (ch < 2971) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 2973) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3002) {
                        if (ch < 2981) {
                          if (ch < 2976) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 2979) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 2987) {
                            if (ch < 2984) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 2990) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3009) {
                          if (ch < 3006) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3008) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 3014) {
                            if (ch < 3011) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3017) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3072) {
                      if (ch < 3032) {
                        if (ch < 3024) {
                          if (ch < 3021) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3022) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3025) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3031) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3059) {
                          if (ch < 3046) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3056) {
                              counts[nd] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        } else {
                          if (ch < 3066) {
                            if (ch < 3065) {
                              counts[so] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          } else {
                            if (ch < 3067) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3090) {
                        if (ch < 3077) {
                          if (ch < 3073) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3076) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3086) {
                            if (ch < 3085) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3089) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3130) {
                          if (ch < 3113) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3114) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 3134) {
                            if (ch < 3133) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 3137) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3252) {
                    if (ch < 3184) {
                      if (ch < 3159) {
                        if (ch < 3146) {
                          if (ch < 3142) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3145) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3150) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3157) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3168) {
                          if (ch < 3160) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3162) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3172) {
                            if (ch < 3170) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 3174) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
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
                            if (ch < 3199) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 3202) {
                            if (ch < 3201) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 3204) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3217) {
                          if (ch < 3213) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3214) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 3241) {
                            if (ch < 3218) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 3242) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3278) {
                      if (ch < 3264) {
                        if (ch < 3260) {
                          if (ch < 3253) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3258) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3262) {
                            if (ch < 3261) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
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
                          if (ch < 3269) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3270) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 3274) {
                            if (ch < 3273) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3276) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3300) {
                        if (ch < 3294) {
                          if (ch < 3285) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3287) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3296) {
                            if (ch < 3295) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3298) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3313) {
                          if (ch < 3302) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3312) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3329) {
                            if (ch < 3315) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3330) {
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
                if (ch < 3585) {
                  if (ch < 3456) {
                    if (ch < 3402) {
                      if (ch < 3387) {
                        if (ch < 3342) {
                          if (ch < 3333) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3341) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3345) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3346) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3393) {
                          if (ch < 3389) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3390) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 3398) {
                            if (ch < 3397) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3401) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3426) {
                        if (ch < 3407) {
                          if (ch < 3405) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3406) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 3416) {
                            if (ch < 3415) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 3424) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3440) {
                          if (ch < 3428) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3430) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        } else {
                          if (ch < 3449) {
                            if (ch < 3446) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3450) {
                              counts[so] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3530) {
                      if (ch < 3506) {
                        if (ch < 3461) {
                          if (ch < 3458) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3460) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3479) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3482) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3517) {
                          if (ch < 3507) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3516) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3520) {
                            if (ch < 3518) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3527) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3544) {
                        if (ch < 3538) {
                          if (ch < 3531) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3535) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 3542) {
                            if (ch < 3541) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3543) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3568) {
                          if (ch < 3552) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 3558) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        } else {
                          if (ch < 3572) {
                            if (ch < 3570) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 3573) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3745) {
                    if (ch < 3713) {
                      if (ch < 3648) {
                        if (ch < 3636) {
                          if (ch < 3633) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3634) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 3643) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3647) {
                              counts[unknown] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3663) {
                          if (ch < 3654) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3655) {
                              counts[lm] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 3674) {
                            if (ch < 3664) {
                              counts[po] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          } else {
                            if (ch < 3676) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3723) {
                        if (ch < 3717) {
                          if (ch < 3715) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3716) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 3721) {
                            if (ch < 3719) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 3722) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3732) {
                          if (ch < 3725) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3726) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3737) {
                            if (ch < 3736) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3744) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3773) {
                      if (ch < 3756) {
                        if (ch < 3750) {
                          if (ch < 3748) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3749) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 3752) {
                            if (ch < 3751) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 3754) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3762) {
                          if (ch < 3757) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3761) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 3770) {
                            if (ch < 3764) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 3771) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3790) {
                        if (ch < 3781) {
                          if (ch < 3774) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 3776) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 3783) {
                            if (ch < 3782) {
                              counts[unknown] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          } else {
                            if (ch < 3784) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3804) {
                          if (ch < 3792) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3802) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3840) {
                            if (ch < 3808) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 3841) {
                              counts[lo] += 1;
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
              if (ch < 4806) {
                if (ch < 4176) {
                  if (ch < 3974) {
                    if (ch < 3897) {
                      if (ch < 3872) {
                        if (ch < 3861) {
                          if (ch < 3859) {
                            counts[po] += 1;
                          } else {
                            if (ch < 3860) {
                              counts[so] += 1;
                            } else {
                              counts[po] += 1;
                            }
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
                        if (ch < 3893) {
                          if (ch < 3882) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 3892) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 3895) {
                            if (ch < 3894) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 3896) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 3912) {
                        if (ch < 3900) {
                          if (ch < 3898) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3899) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
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
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 3953) {
                          if (ch < 3913) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 3949) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 3968) {
                            if (ch < 3967) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 3973) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4057) {
                      if (ch < 4030) {
                        if (ch < 3992) {
                          if (ch < 3976) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 3981) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 3993) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 4029) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4045) {
                          if (ch < 4038) {
                            counts[so] += 1;
                          } else {
                            if (ch < 4039) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 4048) {
                            if (ch < 4046) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 4053) {
                              counts[po] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4152) {
                        if (ch < 4139) {
                          if (ch < 4059) {
                            counts[po] += 1;
                          } else {
                            if (ch < 4096) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 4145) {
                            if (ch < 4141) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 4146) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4157) {
                          if (ch < 4153) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4155) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
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
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 4301) {
                    if (ch < 4227) {
                      if (ch < 4194) {
                        if (ch < 4186) {
                          if (ch < 4182) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 4184) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
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
                      } else {
                        if (ch < 4206) {
                          if (ch < 4197) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4199) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 4213) {
                            if (ch < 4209) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 4226) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4250) {
                        if (ch < 4237) {
                          if (ch < 4229) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4231) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
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
                              counts[nd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4256) {
                          if (ch < 4253) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 4254) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 4295) {
                            if (ch < 4294) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 4296) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4702) {
                      if (ch < 4682) {
                        if (ch < 4347) {
                          if (ch < 4302) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 4304) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 4349) {
                            if (ch < 4348) {
                              counts[po] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          } else {
                            if (ch < 4681) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4695) {
                          if (ch < 4686) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 4688) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 4697) {
                            if (ch < 4696) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 4698) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 4786) {
                        if (ch < 4746) {
                          if (ch < 4704) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 4745) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 4752) {
                            if (ch < 4750) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 4785) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4799) {
                          if (ch < 4790) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 4792) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 4801) {
                            if (ch < 4800) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 4802) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 6086) {
                  if (ch < 5792) {
                    if (ch < 4992) {
                      if (ch < 4886) {
                        if (ch < 4824) {
                          if (ch < 4808) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 4823) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 4881) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 4882) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 4957) {
                          if (ch < 4888) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 4955) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 4969) {
                            if (ch < 4960) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 4989) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 5741) {
                        if (ch < 5024) {
                          if (ch < 5008) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 5018) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 5120) {
                            if (ch < 5109) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 5121) {
                              counts[pd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 5761) {
                          if (ch < 5743) {
                            counts[po] += 1;
                          } else {
                            if (ch < 5760) {
                              counts[lo] += 1;
                            } else {
                              counts[zs] += 1;
                            }
                          }
                        } else {
                          if (ch < 5788) {
                            if (ch < 5787) {
                              counts[lo] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          } else {
                            if (ch < 5789) {
                              counts[pe] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 5952) {
                      if (ch < 5902) {
                        if (ch < 5873) {
                          if (ch < 5867) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 5870) {
                              counts[po] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          }
                        } else {
                          if (ch < 5888) {
                            if (ch < 5881) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 5901) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 5920) {
                          if (ch < 5906) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 5909) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 5941) {
                            if (ch < 5938) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 5943) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6002) {
                        if (ch < 5984) {
                          if (ch < 5970) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 5972) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 5998) {
                            if (ch < 5997) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 6001) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6068) {
                          if (ch < 6004) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6016) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 6071) {
                            if (ch < 6070) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 6078) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 6313) {
                    if (ch < 6138) {
                      if (ch < 6107) {
                        if (ch < 6100) {
                          if (ch < 6087) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6089) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 6103) {
                            counts[po] += 1;
                          } else {
                            if (ch < 6104) {
                              counts[lm] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6110) {
                          if (ch < 6108) {
                            counts[sc] += 1;
                          } else {
                            if (ch < 6109) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 6122) {
                            if (ch < 6112) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          } else {
                            if (ch < 6128) {
                              counts[unknown] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6160) {
                        if (ch < 6151) {
                          if (ch < 6144) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 6150) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        } else {
                          if (ch < 6158) {
                            if (ch < 6155) {
                              counts[po] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 6159) {
                              counts[cf] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6211) {
                          if (ch < 6170) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 6176) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 6264) {
                            if (ch < 6212) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 6272) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6451) {
                      if (ch < 6432) {
                        if (ch < 6320) {
                          if (ch < 6314) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6315) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 6400) {
                            if (ch < 6390) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 6431) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6441) {
                          if (ch < 6435) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6439) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 6448) {
                            if (ch < 6444) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
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
                            if (ch < 6460) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 6468) {
                            if (ch < 6465) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 6470) {
                              counts[po] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6517) {
                          if (ch < 6510) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6512) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 6572) {
                            if (ch < 6528) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 6576) {
                              counts[unknown] += 1;
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
            }
          } else {
            if (ch < 7778) {
              if (ch < 7416) {
                if (ch < 7009) {
                  if (ch < 6783) {
                    if (ch < 6688) {
                      if (ch < 6622) {
                        if (ch < 6608) {
                          if (ch < 6600) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6602) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 6618) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 6619) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6681) {
                          if (ch < 6656) {
                            counts[so] += 1;
                          } else {
                            if (ch < 6679) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 6684) {
                            if (ch < 6683) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 6686) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6753) {
                        if (ch < 6743) {
                          if (ch < 6741) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 6742) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 6751) {
                            if (ch < 6744) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 6752) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6757) {
                          if (ch < 6754) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6755) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
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
                            if (ch < 6781) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6916) {
                      if (ch < 6823) {
                        if (ch < 6800) {
                          if (ch < 6784) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 6794) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 6810) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 6816) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6832) {
                          if (ch < 6824) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 6830) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 6847) {
                            if (ch < 6846) {
                              counts[mn] += 1;
                            } else {
                              counts[me] += 1;
                            }
                          } else {
                            if (ch < 6912) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 6973) {
                        if (ch < 6965) {
                          if (ch < 6917) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6964) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 6971) {
                            if (ch < 6966) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 6972) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 6981) {
                          if (ch < 6978) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 6979) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 6992) {
                            if (ch < 6988) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 7002) {
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
                  if (ch < 7204) {
                    if (ch < 7086) {
                      if (ch < 7043) {
                        if (ch < 7037) {
                          if (ch < 7019) {
                            counts[so] += 1;
                          } else {
                            if (ch < 7028) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 7040) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 7042) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7078) {
                          if (ch < 7073) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 7074) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 7082) {
                            if (ch < 7080) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
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
                      if (ch < 7149) {
                        if (ch < 7142) {
                          if (ch < 7088) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 7098) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 7144) {
                            if (ch < 7143) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 7146) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7154) {
                          if (ch < 7150) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 7151) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 7164) {
                            if (ch < 7156) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 7168) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7360) {
                      if (ch < 7242) {
                        if (ch < 7222) {
                          if (ch < 7212) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 7220) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 7227) {
                            if (ch < 7224) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 7232) {
                              counts[po] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7258) {
                          if (ch < 7245) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 7248) {
                              counts[lo] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        } else {
                          if (ch < 7294) {
                            if (ch < 7288) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          } else {
                            if (ch < 7296) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7401) {
                        if (ch < 7379) {
                          if (ch < 7368) {
                            counts[po] += 1;
                          } else {
                            if (ch < 7376) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
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
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7410) {
                          if (ch < 7405) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 7406) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 7413) {
                            if (ch < 7412) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 7415) {
                              counts[lo] += 1;
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
                if (ch < 7723) {
                  if (ch < 7696) {
                    if (ch < 7682) {
                      if (ch < 7545) {
                        if (ch < 7468) {
                          if (ch < 7418) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 7424) {
                              counts[unknown] += 1;
                            } else {
                              counts[ll] += 1;
                            }
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
                      } else {
                        if (ch < 7670) {
                          if (ch < 7579) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7616) {
                              counts[lm] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 7680) {
                            if (ch < 7676) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 7681) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7689) {
                        if (ch < 7685) {
                          if (ch < 7683) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7684) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7687) {
                            if (ch < 7686) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7688) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7692) {
                          if (ch < 7690) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7691) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7709) {
                      if (ch < 7702) {
                        if (ch < 7699) {
                          if (ch < 7697) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7698) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
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
                        if (ch < 7705) {
                          if (ch < 7703) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7704) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7707) {
                            if (ch < 7706) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7708) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7716) {
                        if (ch < 7712) {
                          if (ch < 7710) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7711) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7719) {
                          if (ch < 7717) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7718) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7721) {
                            if (ch < 7720) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7722) {
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
                  if (ch < 7750) {
                    if (ch < 7736) {
                      if (ch < 7729) {
                        if (ch < 7726) {
                          if (ch < 7724) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7725) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7727) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7728) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7732) {
                          if (ch < 7730) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7731) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7743) {
                        if (ch < 7739) {
                          if (ch < 7737) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7738) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7741) {
                            if (ch < 7740) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7742) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7746) {
                          if (ch < 7744) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7745) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7748) {
                            if (ch < 7747) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7749) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7764) {
                      if (ch < 7757) {
                        if (ch < 7753) {
                          if (ch < 7751) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7752) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7755) {
                            if (ch < 7754) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7756) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7760) {
                          if (ch < 7758) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7759) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7762) {
                            if (ch < 7761) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7763) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7771) {
                        if (ch < 7767) {
                          if (ch < 7765) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7766) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7774) {
                          if (ch < 7772) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7773) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7776) {
                            if (ch < 7775) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7777) {
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
              if (ch < 7895) {
                if (ch < 7840) {
                  if (ch < 7805) {
                    if (ch < 7791) {
                      if (ch < 7784) {
                        if (ch < 7781) {
                          if (ch < 7779) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7780) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7782) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7783) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7787) {
                          if (ch < 7785) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7786) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7798) {
                        if (ch < 7794) {
                          if (ch < 7792) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7793) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7796) {
                            if (ch < 7795) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7797) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7801) {
                          if (ch < 7799) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7800) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7803) {
                            if (ch < 7802) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7804) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7818) {
                      if (ch < 7811) {
                        if (ch < 7808) {
                          if (ch < 7806) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7807) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7809) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7810) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7814) {
                          if (ch < 7812) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7813) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7816) {
                            if (ch < 7815) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7817) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7825) {
                        if (ch < 7821) {
                          if (ch < 7819) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7820) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7823) {
                            if (ch < 7822) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7824) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7828) {
                          if (ch < 7826) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7827) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7838) {
                            if (ch < 7829) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7839) {
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
                  if (ch < 7867) {
                    if (ch < 7853) {
                      if (ch < 7846) {
                        if (ch < 7843) {
                          if (ch < 7841) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7842) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7844) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7845) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7849) {
                          if (ch < 7847) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7848) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7851) {
                            if (ch < 7850) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7852) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7860) {
                        if (ch < 7856) {
                          if (ch < 7854) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7855) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7858) {
                            if (ch < 7857) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7859) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7863) {
                          if (ch < 7861) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7862) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7865) {
                            if (ch < 7864) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7866) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7881) {
                      if (ch < 7874) {
                        if (ch < 7870) {
                          if (ch < 7868) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7869) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7877) {
                          if (ch < 7875) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7876) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7879) {
                            if (ch < 7878) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7880) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7888) {
                        if (ch < 7884) {
                          if (ch < 7882) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7883) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7886) {
                            if (ch < 7885) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7887) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7891) {
                          if (ch < 7889) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7890) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7893) {
                            if (ch < 7892) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
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
              } else {
                if (ch < 8024) {
                  if (ch < 7922) {
                    if (ch < 7908) {
                      if (ch < 7901) {
                        if (ch < 7898) {
                          if (ch < 7896) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7897) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7899) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7900) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7904) {
                          if (ch < 7902) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7903) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7906) {
                            if (ch < 7905) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7907) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7915) {
                        if (ch < 7911) {
                          if (ch < 7909) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7910) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 7913) {
                            if (ch < 7912) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 7914) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7918) {
                          if (ch < 7916) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7917) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7920) {
                            if (ch < 7919) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7921) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7944) {
                      if (ch < 7929) {
                        if (ch < 7925) {
                          if (ch < 7923) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7924) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 7932) {
                          if (ch < 7930) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 7931) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 7934) {
                            if (ch < 7933) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 7935) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 7984) {
                        if (ch < 7960) {
                          if (ch < 7952) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 7958) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 7968) {
                            if (ch < 7966) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 7976) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8006) {
                          if (ch < 7992) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8000) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 8014) {
                            if (ch < 8008) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 8016) {
                              counts[unknown] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 8133) {
                    if (ch < 8072) {
                      if (ch < 8030) {
                        if (ch < 8027) {
                          if (ch < 8025) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 8026) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 8028) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8029) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8040) {
                          if (ch < 8031) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 8032) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 8062) {
                            if (ch < 8048) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 8064) {
                              counts[unknown] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8118) {
                        if (ch < 8096) {
                          if (ch < 8080) {
                            counts[lt] += 1;
                          } else {
                            if (ch < 8088) {
                              counts[ll] += 1;
                            } else {
                              counts[lt] += 1;
                            }
                          }
                        } else {
                          if (ch < 8112) {
                            if (ch < 8104) {
                              counts[ll] += 1;
                            } else {
                              counts[lt] += 1;
                            }
                          } else {
                            if (ch < 8117) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8125) {
                          if (ch < 8120) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8124) {
                              counts[lu] += 1;
                            } else {
                              counts[lt] += 1;
                            }
                          }
                        } else {
                          if (ch < 8127) {
                            if (ch < 8126) {
                              counts[sk] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 8130) {
                              counts[sk] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8176) {
                      if (ch < 8150) {
                        if (ch < 8140) {
                          if (ch < 8134) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 8136) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 8144) {
                            if (ch < 8141) {
                              counts[lt] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          } else {
                            if (ch < 8148) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8157) {
                          if (ch < 8152) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8156) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 8168) {
                            if (ch < 8160) {
                              counts[sk] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 8173) {
                              counts[lu] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8191) {
                        if (ch < 8182) {
                          if (ch < 8178) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 8181) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 8188) {
                            if (ch < 8184) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 8189) {
                              counts[lt] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8208) {
                          if (ch < 8192) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 8203) {
                              counts[zs] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        } else {
                          if (ch < 8216) {
                            if (ch < 8214) {
                              counts[pd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 8217) {
                              counts[pi] += 1;
                            } else {
                              counts[pf] += 1;
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
        if (ch < 43760) {
          if (ch < 12272) {
            if (ch < 11079) {
              if (ch < 8623) {
                if (ch < 8455) {
                  if (ch < 8294) {
                    if (ch < 8251) {
                      if (ch < 8232) {
                        if (ch < 8222) {
                          if (ch < 8219) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 8221) {
                              counts[pi] += 1;
                            } else {
                              counts[pf] += 1;
                            }
                          }
                        } else {
                          if (ch < 8223) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 8224) {
                              counts[pi] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8239) {
                          if (ch < 8233) {
                            counts[zl] += 1;
                          } else {
                            if (ch < 8234) {
                              counts[zp] += 1;
                            } else {
                              counts[cf] += 1;
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
                              counts[pf] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8274) {
                        if (ch < 8260) {
                          if (ch < 8255) {
                            counts[po] += 1;
                          } else {
                            if (ch < 8257) {
                              counts[pc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 8262) {
                            if (ch < 8261) {
                              counts[sm] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          } else {
                            if (ch < 8263) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8277) {
                          if (ch < 8275) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8276) {
                              counts[po] += 1;
                            } else {
                              counts[pc] += 1;
                            }
                          }
                        } else {
                          if (ch < 8288) {
                            if (ch < 8287) {
                              counts[po] += 1;
                            } else {
                              counts[zs] += 1;
                            }
                          } else {
                            if (ch < 8293) {
                              counts[cf] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8335) {
                      if (ch < 8317) {
                        if (ch < 8306) {
                          if (ch < 8304) {
                            counts[cf] += 1;
                          } else {
                            if (ch < 8305) {
                              counts[no] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 8308) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 8314) {
                              counts[no] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8320) {
                          if (ch < 8318) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 8319) {
                              counts[pe] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 8333) {
                            if (ch < 8330) {
                              counts[no] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          } else {
                            if (ch < 8334) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8417) {
                        if (ch < 8352) {
                          if (ch < 8336) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 8349) {
                              counts[lm] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 8400) {
                            if (ch < 8382) {
                              counts[sc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 8413) {
                              counts[mn] += 1;
                            } else {
                              counts[me] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8433) {
                          if (ch < 8418) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 8421) {
                              counts[me] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 8450) {
                            if (ch < 8448) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 8451) {
                              counts[lu] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 8508) {
                    if (ch < 8484) {
                      if (ch < 8467) {
                        if (ch < 8459) {
                          if (ch < 8456) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8458) {
                              counts[so] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 8462) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8464) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8470) {
                          if (ch < 8468) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8469) {
                              counts[so] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 8473) {
                            if (ch < 8472) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          } else {
                            if (ch < 8478) {
                              counts[lu] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8494) {
                        if (ch < 8487) {
                          if (ch < 8485) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 8486) {
                              counts[so] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 8489) {
                            if (ch < 8488) {
                              counts[so] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 8490) {
                              counts[so] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8500) {
                          if (ch < 8495) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8496) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 8505) {
                            if (ch < 8501) {
                              counts[ll] += 1;
                            } else {
                              counts[lo] += 1;
                            }
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
                  } else {
                    if (ch < 8581) {
                      if (ch < 8524) {
                        if (ch < 8517) {
                          if (ch < 8510) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 8512) {
                              counts[lu] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        } else {
                          if (ch < 8522) {
                            if (ch < 8518) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 8523) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8528) {
                          if (ch < 8526) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8527) {
                              counts[ll] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 8608) {
                        if (ch < 8592) {
                          if (ch < 8585) {
                            counts[nl] += 1;
                          } else {
                            if (ch < 8586) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 8602) {
                            if (ch < 8597) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 8604) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8612) {
                          if (ch < 8609) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8611) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        } else {
                          if (ch < 8615) {
                            if (ch < 8614) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          } else {
                            if (ch < 8622) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 10100) {
                  if (ch < 9255) {
                    if (ch < 8972) {
                      if (ch < 8661) {
                        if (ch < 8658) {
                          if (ch < 8654) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8656) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 8659) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 8660) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 8968) {
                          if (ch < 8692) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8960) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 8970) {
                            if (ch < 8969) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 8971) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 9085) {
                        if (ch < 9001) {
                          if (ch < 8992) {
                            counts[so] += 1;
                          } else {
                            if (ch < 8994) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 9003) {
                            if (ch < 9002) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 9084) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 9180) {
                          if (ch < 9115) {
                            counts[so] += 1;
                          } else {
                            if (ch < 9140) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 9211) {
                            if (ch < 9186) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 9216) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 9839) {
                      if (ch < 9472) {
                        if (ch < 9312) {
                          if (ch < 9280) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 9291) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
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
                        if (ch < 9665) {
                          if (ch < 9655) {
                            counts[so] += 1;
                          } else {
                            if (ch < 9656) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 9720) {
                            if (ch < 9666) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 9728) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10093) {
                        if (ch < 10089) {
                          if (ch < 9840) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 10088) {
                              counts[so] += 1;
                            } else {
                              counts[ps] += 1;
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
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10096) {
                          if (ch < 10094) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10095) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 10098) {
                            if (ch < 10097) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 10099) {
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
                  if (ch < 10633) {
                    if (ch < 10219) {
                      if (ch < 10182) {
                        if (ch < 10132) {
                          if (ch < 10101) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10102) {
                              counts[pe] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        } else {
                          if (ch < 10176) {
                            counts[so] += 1;
                          } else {
                            if (ch < 10181) {
                              counts[sm] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10215) {
                          if (ch < 10183) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10214) {
                              counts[sm] += 1;
                            } else {
                              counts[ps] += 1;
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
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10496) {
                        if (ch < 10222) {
                          if (ch < 10220) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10221) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 10224) {
                            if (ch < 10223) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 10240) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10629) {
                          if (ch < 10627) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 10628) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 10631) {
                            if (ch < 10630) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 10632) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 10647) {
                      if (ch < 10640) {
                        if (ch < 10636) {
                          if (ch < 10634) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10635) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        } else {
                          if (ch < 10638) {
                            if (ch < 10637) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          } else {
                            if (ch < 10639) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10643) {
                          if (ch < 10641) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 10642) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 10645) {
                            if (ch < 10644) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 10646) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 10716) {
                        if (ch < 10712) {
                          if (ch < 10648) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 10649) {
                              counts[pe] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        } else {
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
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 10750) {
                          if (ch < 10748) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 10749) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 11056) {
                            if (ch < 11008) {
                              counts[sm] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 11077) {
                              counts[sm] += 1;
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
              if (ch < 11469) {
                if (ch < 11414) {
                  if (ch < 11378) {
                    if (ch < 11312) {
                      if (ch < 11194) {
                        if (ch < 11126) {
                          if (ch < 11085) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 11124) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 11158) {
                            counts[so] += 1;
                          } else {
                            if (ch < 11160) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11210) {
                          if (ch < 11197) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 11209) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 11264) {
                            if (ch < 11218) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 11311) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11368) {
                        if (ch < 11361) {
                          if (ch < 11359) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11360) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 11365) {
                            if (ch < 11362) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 11367) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11371) {
                          if (ch < 11369) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11370) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 11373) {
                            if (ch < 11372) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 11377) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11400) {
                      if (ch < 11393) {
                        if (ch < 11382) {
                          if (ch < 11379) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11381) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 11388) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11390) {
                              counts[lm] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11396) {
                          if (ch < 11394) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11395) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 11398) {
                            if (ch < 11397) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 11399) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11407) {
                        if (ch < 11403) {
                          if (ch < 11401) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11402) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 11405) {
                            if (ch < 11404) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 11406) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11410) {
                          if (ch < 11408) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11409) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11441) {
                    if (ch < 11427) {
                      if (ch < 11420) {
                        if (ch < 11417) {
                          if (ch < 11415) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11416) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
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
                      } else {
                        if (ch < 11423) {
                          if (ch < 11421) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11422) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 11425) {
                            if (ch < 11424) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 11426) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11434) {
                        if (ch < 11430) {
                          if (ch < 11428) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11429) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11437) {
                          if (ch < 11435) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11436) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 11439) {
                            if (ch < 11438) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 11440) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11455) {
                      if (ch < 11448) {
                        if (ch < 11444) {
                          if (ch < 11442) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11443) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 11446) {
                            if (ch < 11445) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 11447) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11451) {
                          if (ch < 11449) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11450) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 11453) {
                            if (ch < 11452) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 11454) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11462) {
                        if (ch < 11458) {
                          if (ch < 11456) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11457) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 11460) {
                            if (ch < 11459) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 11461) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11465) {
                          if (ch < 11463) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11464) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 11704) {
                  if (ch < 11502) {
                    if (ch < 11482) {
                      if (ch < 11475) {
                        if (ch < 11472) {
                          if (ch < 11470) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11471) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
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
                        if (ch < 11478) {
                          if (ch < 11476) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11477) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 11480) {
                            if (ch < 11479) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 11481) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11489) {
                        if (ch < 11485) {
                          if (ch < 11483) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 11484) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11493) {
                          if (ch < 11490) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11491) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 11500) {
                            if (ch < 11499) {
                              counts[so] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 11501) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11568) {
                      if (ch < 11518) {
                        if (ch < 11507) {
                          if (ch < 11503) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 11506) {
                              counts[mn] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 11513) {
                            if (ch < 11508) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 11517) {
                              counts[po] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11559) {
                          if (ch < 11520) {
                            counts[po] += 1;
                          } else {
                            if (ch < 11558) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 11565) {
                            if (ch < 11560) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 11566) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11671) {
                        if (ch < 11632) {
                          if (ch < 11624) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 11631) {
                              counts[unknown] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 11647) {
                            if (ch < 11633) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 11648) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11688) {
                          if (ch < 11680) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 11687) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 11696) {
                            if (ch < 11695) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 11703) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11804) {
                    if (ch < 11779) {
                      if (ch < 11728) {
                        if (ch < 11719) {
                          if (ch < 11711) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 11712) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 11720) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 11727) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11743) {
                          if (ch < 11735) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 11736) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 11776) {
                            if (ch < 11744) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 11778) {
                              counts[po] += 1;
                            } else {
                              counts[pi] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11788) {
                        if (ch < 11782) {
                          if (ch < 11780) {
                            counts[pf] += 1;
                          } else {
                            if (ch < 11781) {
                              counts[pi] += 1;
                            } else {
                              counts[pf] += 1;
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
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11799) {
                          if (ch < 11789) {
                            counts[pi] += 1;
                          } else {
                            if (ch < 11790) {
                              counts[pf] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 11802) {
                            if (ch < 11800) {
                              counts[pd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 11803) {
                              counts[pd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11823) {
                      if (ch < 11812) {
                        if (ch < 11808) {
                          if (ch < 11805) {
                            counts[pi] += 1;
                          } else {
                            if (ch < 11806) {
                              counts[pf] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 11810) {
                            if (ch < 11809) {
                              counts[pi] += 1;
                            } else {
                              counts[pf] += 1;
                            }
                          } else {
                            if (ch < 11811) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11815) {
                          if (ch < 11813) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 11814) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        } else {
                          if (ch < 11817) {
                            if (ch < 11816) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          } else {
                            if (ch < 11818) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 11843) {
                        if (ch < 11836) {
                          if (ch < 11824) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 11834) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        } else {
                          if (ch < 11841) {
                            if (ch < 11840) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          } else {
                            if (ch < 11842) {
                              counts[po] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 11931) {
                          if (ch < 11904) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 11930) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 12032) {
                            if (ch < 12020) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 12246) {
                              counts[so] += 1;
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
            if (ch < 42808) {
              if (ch < 42563) {
                if (ch < 12544) {
                  if (ch < 12316) {
                    if (ch < 12301) {
                      if (ch < 12294) {
                        if (ch < 12289) {
                          if (ch < 12284) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12288) {
                              counts[unknown] += 1;
                            } else {
                              counts[zs] += 1;
                            }
                          }
                        } else {
                          if (ch < 12292) {
                            counts[po] += 1;
                          } else {
                            if (ch < 12293) {
                              counts[so] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12297) {
                          if (ch < 12295) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 12296) {
                              counts[nl] += 1;
                            } else {
                              counts[ps] += 1;
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
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12309) {
                        if (ch < 12304) {
                          if (ch < 12302) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 12303) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 12306) {
                            if (ch < 12305) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 12308) {
                              counts[so] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12312) {
                          if (ch < 12310) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 12311) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 12314) {
                            if (ch < 12313) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 12315) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12349) {
                      if (ch < 12334) {
                        if (ch < 12320) {
                          if (ch < 12317) {
                            counts[pd] += 1;
                          } else {
                            if (ch < 12318) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 12321) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12330) {
                              counts[nl] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12342) {
                          if (ch < 12336) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 12337) {
                              counts[pd] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 12347) {
                            if (ch < 12344) {
                              counts[so] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          } else {
                            if (ch < 12348) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12445) {
                        if (ch < 12353) {
                          if (ch < 12350) {
                            counts[po] += 1;
                          } else {
                            if (ch < 12352) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 12441) {
                            if (ch < 12439) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 12443) {
                              counts[mn] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12449) {
                          if (ch < 12447) {
                            counts[lm] += 1;
                          } else {
                            if (ch < 12448) {
                              counts[lo] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        } else {
                          if (ch < 12540) {
                            if (ch < 12539) {
                              counts[lo] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 12543) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 13312) {
                    if (ch < 12800) {
                      if (ch < 12690) {
                        if (ch < 12593) {
                          if (ch < 12549) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 12590) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 12687) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 12688) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12731) {
                          if (ch < 12694) {
                            counts[no] += 1;
                          } else {
                            if (ch < 12704) {
                              counts[so] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 12772) {
                            if (ch < 12736) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 12784) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 12896) {
                        if (ch < 12842) {
                          if (ch < 12831) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12832) {
                              counts[unknown] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        } else {
                          if (ch < 12880) {
                            if (ch < 12872) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          } else {
                            if (ch < 12881) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 12977) {
                          if (ch < 12928) {
                            counts[so] += 1;
                          } else {
                            if (ch < 12938) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 13055) {
                            if (ch < 12992) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 13056) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42183) {
                      if (ch < 40908) {
                        if (ch < 19894) {
                          if (ch < 13313) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 19893) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 19968) {
                            if (ch < 19904) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 19969) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 40981) {
                          if (ch < 40909) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 40960) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 42125) {
                            if (ch < 40982) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 42128) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42512) {
                        if (ch < 42238) {
                          if (ch < 42192) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 42232) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 42508) {
                            if (ch < 42240) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 42509) {
                              counts[lm] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42540) {
                          if (ch < 42528) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 42538) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 42561) {
                            if (ch < 42560) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42562) {
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
                if (ch < 42628) {
                  if (ch < 42590) {
                    if (ch < 42576) {
                      if (ch < 42569) {
                        if (ch < 42566) {
                          if (ch < 42564) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42565) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42567) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42568) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42572) {
                          if (ch < 42570) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42571) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42574) {
                            if (ch < 42573) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 42575) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42583) {
                        if (ch < 42579) {
                          if (ch < 42577) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42578) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42581) {
                            if (ch < 42580) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42582) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42586) {
                          if (ch < 42584) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42585) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42588) {
                            if (ch < 42587) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
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
                    if (ch < 42603) {
                      if (ch < 42596) {
                        if (ch < 42593) {
                          if (ch < 42591) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42592) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42594) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42595) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42599) {
                          if (ch < 42597) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42598) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42601) {
                            if (ch < 42600) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42602) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42612) {
                        if (ch < 42606) {
                          if (ch < 42604) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42605) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42608) {
                            if (ch < 42607) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 42611) {
                              counts[me] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42624) {
                          if (ch < 42622) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 42623) {
                              counts[po] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 42626) {
                            if (ch < 42625) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 42627) {
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
                  if (ch < 42656) {
                    if (ch < 42641) {
                      if (ch < 42634) {
                        if (ch < 42631) {
                          if (ch < 42629) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42630) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42632) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42633) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42637) {
                          if (ch < 42635) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42636) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42639) {
                            if (ch < 42638) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42640) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42648) {
                        if (ch < 42644) {
                          if (ch < 42642) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42643) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42646) {
                            if (ch < 42645) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 42647) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42651) {
                          if (ch < 42649) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42650) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42654) {
                            if (ch < 42652) {
                              counts[ll] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          } else {
                            if (ch < 42655) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42792) {
                      if (ch < 42784) {
                        if (ch < 42738) {
                          if (ch < 42726) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 42736) {
                              counts[nl] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 42752) {
                            if (ch < 42744) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 42775) {
                              counts[sk] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42788) {
                          if (ch < 42786) {
                            counts[sk] += 1;
                          } else {
                            if (ch < 42787) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42790) {
                            if (ch < 42789) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 42791) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42799) {
                        if (ch < 42795) {
                          if (ch < 42793) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42794) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42797) {
                            if (ch < 42796) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42798) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42804) {
                          if (ch < 42802) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42803) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42806) {
                            if (ch < 42805) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
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
                  }
                }
              }
            } else {
              if (ch < 43002) {
                if (ch < 42862) {
                  if (ch < 42835) {
                    if (ch < 42821) {
                      if (ch < 42814) {
                        if (ch < 42811) {
                          if (ch < 42809) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42810) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42812) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42813) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42817) {
                          if (ch < 42815) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42816) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42819) {
                            if (ch < 42818) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42820) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42828) {
                        if (ch < 42824) {
                          if (ch < 42822) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42823) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42826) {
                            if (ch < 42825) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 42827) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42831) {
                          if (ch < 42829) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42830) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42833) {
                            if (ch < 42832) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42834) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 42848) {
                      if (ch < 42841) {
                        if (ch < 42838) {
                          if (ch < 42836) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42837) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42839) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42840) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42844) {
                          if (ch < 42842) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42843) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 42846) {
                            if (ch < 42845) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 42847) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42855) {
                        if (ch < 42851) {
                          if (ch < 42849) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42850) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42853) {
                            if (ch < 42852) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42854) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42858) {
                          if (ch < 42856) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42857) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 42898) {
                    if (ch < 42883) {
                      if (ch < 42875) {
                        if (ch < 42865) {
                          if (ch < 42863) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42864) {
                              counts[ll] += 1;
                            } else {
                              counts[lm] += 1;
                            }
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
                      } else {
                        if (ch < 42879) {
                          if (ch < 42876) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42877) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42881) {
                            if (ch < 42880) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42882) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42891) {
                        if (ch < 42886) {
                          if (ch < 42884) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42885) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[sk] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42894) {
                          if (ch < 42892) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42893) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42896) {
                            if (ch < 42895) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
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
                    if (ch < 42914) {
                      if (ch < 42907) {
                        if (ch < 42903) {
                          if (ch < 42899) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42902) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42905) {
                            if (ch < 42904) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42906) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42910) {
                          if (ch < 42908) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42909) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
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
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 42921) {
                        if (ch < 42917) {
                          if (ch < 42915) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 42916) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 42919) {
                            if (ch < 42918) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 42920) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 42928) {
                          if (ch < 42922) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 42926) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 42999) {
                            if (ch < 42930) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 43000) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 43470) {
                  if (ch < 43216) {
                    if (ch < 43056) {
                      if (ch < 43019) {
                        if (ch < 43011) {
                          if (ch < 43003) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 43010) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 43014) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43015) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43045) {
                          if (ch < 43020) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43043) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 43048) {
                            if (ch < 43047) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 43052) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43128) {
                        if (ch < 43065) {
                          if (ch < 43062) {
                            counts[no] += 1;
                          } else {
                            if (ch < 43064) {
                              counts[so] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        } else {
                          if (ch < 43072) {
                            if (ch < 43066) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 43124) {
                              counts[lo] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43188) {
                          if (ch < 43136) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 43138) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 43205) {
                            if (ch < 43204) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 43214) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43348) {
                      if (ch < 43264) {
                        if (ch < 43250) {
                          if (ch < 43226) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 43232) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 43259) {
                            if (ch < 43256) {
                              counts[lo] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 43260) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43310) {
                          if (ch < 43274) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 43302) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 43335) {
                            if (ch < 43312) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 43346) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43443) {
                        if (ch < 43389) {
                          if (ch < 43359) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 43360) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 43395) {
                            if (ch < 43392) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 43396) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43450) {
                          if (ch < 43444) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43446) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 43453) {
                            if (ch < 43452) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 43457) {
                              counts[mc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 43612) {
                    if (ch < 43561) {
                      if (ch < 43493) {
                        if (ch < 43482) {
                          if (ch < 43471) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 43472) {
                              counts[lm] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        } else {
                          if (ch < 43486) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 43488) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43504) {
                          if (ch < 43494) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43495) {
                              counts[lm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 43519) {
                            if (ch < 43514) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 43520) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43587) {
                        if (ch < 43571) {
                          if (ch < 43567) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43569) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 43575) {
                            if (ch < 43573) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 43584) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43597) {
                          if (ch < 43588) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43596) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 43600) {
                            if (ch < 43598) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 43610) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43703) {
                      if (ch < 43644) {
                        if (ch < 43633) {
                          if (ch < 43616) {
                            counts[po] += 1;
                          } else {
                            if (ch < 43632) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
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
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43696) {
                          if (ch < 43645) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43646) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 43698) {
                            if (ch < 43697) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 43701) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43739) {
                        if (ch < 43712) {
                          if (ch < 43705) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 43710) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 43714) {
                            if (ch < 43713) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 43715) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43744) {
                          if (ch < 43741) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43742) {
                              counts[lm] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 43756) {
                            if (ch < 43755) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 43758) {
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
            }
          }
        } else {
          if (ch < 70379) {
            if (ch < 65787) {
              if (ch < 65086) {
                if (ch < 64112) {
                  if (ch < 44009) {
                    if (ch < 43815) {
                      if (ch < 43777) {
                        if (ch < 43765) {
                          if (ch < 43762) {
                            counts[po] += 1;
                          } else {
                            if (ch < 43763) {
                              counts[lo] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          }
                        } else {
                          if (ch < 43766) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 43767) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 43791) {
                          if (ch < 43783) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 43785) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 43799) {
                            if (ch < 43793) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 43808) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 43876) {
                        if (ch < 43824) {
                          if (ch < 43816) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 43823) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 43868) {
                            if (ch < 43867) {
                              counts[ll] += 1;
                            } else {
                              counts[sk] += 1;
                            }
                          } else {
                            if (ch < 43872) {
                              counts[lm] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 44003) {
                          if (ch < 43878) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 43968) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 44006) {
                            if (ch < 44005) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 44008) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 55243) {
                      if (ch < 44026) {
                        if (ch < 44013) {
                          if (ch < 44011) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 44012) {
                              counts[po] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 44014) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 44016) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 55203) {
                          if (ch < 44032) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 44033) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 55216) {
                            if (ch < 55204) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 55239) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 56321) {
                        if (ch < 55297) {
                          if (ch < 55292) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 55296) {
                              counts[unknown] += 1;
                            } else {
                              counts[cs] += 1;
                            }
                          }
                        } else {
                          if (ch < 56193) {
                            if (ch < 56191) {
                              counts[unknown] += 1;
                            } else {
                              counts[cs] += 1;
                            }
                          } else {
                            if (ch < 56319) {
                              counts[unknown] += 1;
                            } else {
                              counts[cs] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 57345) {
                          if (ch < 57343) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 57344) {
                              counts[cs] += 1;
                            } else {
                              counts[co] += 1;
                            }
                          }
                        } else {
                          if (ch < 63744) {
                            if (ch < 63743) {
                              counts[unknown] += 1;
                            } else {
                              counts[co] += 1;
                            }
                          } else {
                            if (ch < 64110) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 64848) {
                    if (ch < 64317) {
                      if (ch < 64285) {
                        if (ch < 64263) {
                          if (ch < 64218) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 64256) {
                              counts[unknown] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 64275) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 64280) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 64297) {
                          if (ch < 64286) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 64287) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 64311) {
                            if (ch < 64298) {
                              counts[sm] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 64312) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 64326) {
                        if (ch < 64320) {
                          if (ch < 64318) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 64319) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 64323) {
                            if (ch < 64322) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 64325) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 64467) {
                          if (ch < 64434) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 64450) {
                              counts[sk] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 64831) {
                            if (ch < 64830) {
                              counts[lo] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 64832) {
                              counts[ps] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65056) {
                      if (ch < 65022) {
                        if (ch < 64968) {
                          if (ch < 64912) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 64914) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 65020) {
                            if (ch < 65008) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
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
                          if (ch < 65024) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 65040) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 65049) {
                            if (ch < 65048) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 65050) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65079) {
                        if (ch < 65073) {
                          if (ch < 65070) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 65072) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 65077) {
                            if (ch < 65075) {
                              counts[pd] += 1;
                            } else {
                              counts[pc] += 1;
                            }
                          } else {
                            if (ch < 65078) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65082) {
                          if (ch < 65080) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65081) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        } else {
                          if (ch < 65084) {
                            if (ch < 65083) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          } else {
                            if (ch < 65085) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 65341) {
                  if (ch < 65128) {
                    if (ch < 65107) {
                      if (ch < 65092) {
                        if (ch < 65089) {
                          if (ch < 65087) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65088) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        } else {
                          if (ch < 65090) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65091) {
                              counts[pe] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65096) {
                          if (ch < 65093) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65095) {
                              counts[po] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        } else {
                          if (ch < 65101) {
                            if (ch < 65097) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 65104) {
                              counts[pc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65117) {
                        if (ch < 65113) {
                          if (ch < 65108) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 65112) {
                              counts[po] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          }
                        } else {
                          if (ch < 65115) {
                            if (ch < 65114) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 65116) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65122) {
                          if (ch < 65118) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65119) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 65124) {
                            if (ch < 65123) {
                              counts[sm] += 1;
                            } else {
                              counts[pd] += 1;
                            }
                          } else {
                            if (ch < 65127) {
                              counts[sm] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65288) {
                      if (ch < 65142) {
                        if (ch < 65132) {
                          if (ch < 65129) {
                            counts[po] += 1;
                          } else {
                            if (ch < 65130) {
                              counts[sc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 65136) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 65141) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65280) {
                          if (ch < 65277) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 65279) {
                              counts[unknown] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        } else {
                          if (ch < 65284) {
                            if (ch < 65281) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 65285) {
                              counts[sc] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65296) {
                        if (ch < 65291) {
                          if (ch < 65289) {
                            counts[ps] += 1;
                          } else {
                            if (ch < 65290) {
                              counts[pe] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 65293) {
                            if (ch < 65292) {
                              counts[sm] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 65294) {
                              counts[pd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65311) {
                          if (ch < 65306) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 65308) {
                              counts[po] += 1;
                            } else {
                              counts[sm] += 1;
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
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 65498) {
                    if (ch < 65379) {
                      if (ch < 65372) {
                        if (ch < 65344) {
                          if (ch < 65342) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65343) {
                              counts[sk] += 1;
                            } else {
                              counts[pc] += 1;
                            }
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
                        if (ch < 65375) {
                          if (ch < 65373) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 65374) {
                              counts[pe] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        } else {
                          if (ch < 65377) {
                            if (ch < 65376) {
                              counts[ps] += 1;
                            } else {
                              counts[pe] += 1;
                            }
                          } else {
                            if (ch < 65378) {
                              counts[po] += 1;
                            } else {
                              counts[ps] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65471) {
                        if (ch < 65392) {
                          if (ch < 65380) {
                            counts[pe] += 1;
                          } else {
                            if (ch < 65382) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
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
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65482) {
                          if (ch < 65474) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 65480) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 65490) {
                            if (ch < 65488) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 65496) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65534) {
                      if (ch < 65511) {
                        if (ch < 65506) {
                          if (ch < 65501) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 65504) {
                              counts[unknown] += 1;
                            } else {
                              counts[sc] += 1;
                            }
                          }
                        } else {
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
                              counts[sc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65517) {
                          if (ch < 65512) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 65513) {
                              counts[so] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        } else {
                          if (ch < 65529) {
                            if (ch < 65519) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 65532) {
                              counts[cf] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 65596) {
                        if (ch < 65549) {
                          if (ch < 65536) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 65548) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 65576) {
                            if (ch < 65575) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 65595) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65614) {
                          if (ch < 65598) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 65599) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 65630) {
                            if (ch < 65616) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 65664) {
                              counts[unknown] += 1;
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
              if (ch < 68152) {
                if (ch < 66864) {
                  if (ch < 66336) {
                    if (ch < 65948) {
                      if (ch < 65856) {
                        if (ch < 65799) {
                          if (ch < 65792) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 65795) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 65844) {
                            counts[no] += 1;
                          } else {
                            if (ch < 65847) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 65930) {
                          if (ch < 65909) {
                            counts[nl] += 1;
                          } else {
                            if (ch < 65913) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 65933) {
                            if (ch < 65932) {
                              counts[no] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 65936) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 66205) {
                        if (ch < 66000) {
                          if (ch < 65952) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 65953) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 66046) {
                            if (ch < 66045) {
                              counts[so] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 66176) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 66272) {
                          if (ch < 66208) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 66257) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 66300) {
                            if (ch < 66273) {
                              counts[mn] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          } else {
                            if (ch < 66304) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 66464) {
                      if (ch < 66379) {
                        if (ch < 66369) {
                          if (ch < 66340) {
                            counts[no] += 1;
                          } else {
                            if (ch < 66352) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 66370) {
                            counts[nl] += 1;
                          } else {
                            if (ch < 66378) {
                              counts[lo] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 66427) {
                          if (ch < 66384) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 66422) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 66462) {
                            if (ch < 66432) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 66463) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 66600) {
                        if (ch < 66512) {
                          if (ch < 66500) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 66504) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 66518) {
                            if (ch < 66513) {
                              counts[po] += 1;
                            } else {
                              counts[nl] += 1;
                            }
                          } else {
                            if (ch < 66560) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 66720) {
                          if (ch < 66640) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 66718) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 66816) {
                            if (ch < 66730) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 66856) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 67712) {
                    if (ch < 67593) {
                      if (ch < 67392) {
                        if (ch < 66928) {
                          if (ch < 66916) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 66927) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 67072) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 67383) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 67432) {
                          if (ch < 67414) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 67424) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 67590) {
                            if (ch < 67584) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 67592) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 67647) {
                        if (ch < 67639) {
                          if (ch < 67594) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 67638) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 67644) {
                            if (ch < 67641) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 67645) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 67672) {
                          if (ch < 67670) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 67671) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 67703) {
                            if (ch < 67680) {
                              counts[no] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 67705) {
                              counts[so] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 68030) {
                      if (ch < 67871) {
                        if (ch < 67760) {
                          if (ch < 67743) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 67751) {
                              counts[unknown] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        } else {
                          if (ch < 67862) {
                            if (ch < 67840) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 67868) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 67903) {
                          if (ch < 67872) {
                            counts[po] += 1;
                          } else {
                            if (ch < 67898) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 67968) {
                            if (ch < 67904) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 68024) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 68108) {
                        if (ch < 68097) {
                          if (ch < 68032) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 68096) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 68101) {
                            if (ch < 68100) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 68103) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68117) {
                          if (ch < 68112) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 68116) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 68121) {
                            if (ch < 68120) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 68148) {
                              counts[lo] += 1;
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
                if (ch < 69815) {
                  if (ch < 68448) {
                    if (ch < 68288) {
                      if (ch < 68185) {
                        if (ch < 68160) {
                          if (ch < 68155) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 68159) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 68168) {
                            counts[no] += 1;
                          } else {
                            if (ch < 68176) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68223) {
                          if (ch < 68192) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 68221) {
                              counts[lo] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        } else {
                          if (ch < 68253) {
                            if (ch < 68224) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 68256) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 68343) {
                        if (ch < 68325) {
                          if (ch < 68296) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 68297) {
                              counts[so] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 68331) {
                            if (ch < 68327) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 68336) {
                              counts[no] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68409) {
                          if (ch < 68352) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 68406) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 68438) {
                            if (ch < 68416) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 68440) {
                              counts[unknown] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 69633) {
                      if (ch < 68521) {
                        if (ch < 68480) {
                          if (ch < 68467) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 68472) {
                              counts[unknown] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        } else {
                          if (ch < 68505) {
                            if (ch < 68498) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 68509) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 68681) {
                          if (ch < 68528) {
                            counts[no] += 1;
                          } else {
                            if (ch < 68608) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 69247) {
                            if (ch < 69216) {
                              counts[unknown] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          } else {
                            if (ch < 69632) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 69734) {
                        if (ch < 69688) {
                          if (ch < 69634) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 69635) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 69710) {
                            if (ch < 69703) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 69714) {
                              counts[unknown] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 69762) {
                          if (ch < 69744) {
                            counts[nd] += 1;
                          } else {
                            if (ch < 69759) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 69808) {
                            if (ch < 69763) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 69811) {
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
                  if (ch < 70067) {
                    if (ch < 69932) {
                      if (ch < 69840) {
                        if (ch < 69821) {
                          if (ch < 69817) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 69819) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 69822) {
                            counts[cf] += 1;
                          } else {
                            if (ch < 69826) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 69882) {
                          if (ch < 69865) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 69872) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        } else {
                          if (ch < 69891) {
                            if (ch < 69888) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 69927) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70003) {
                        if (ch < 69942) {
                          if (ch < 69933) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 69941) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 69956) {
                            if (ch < 69952) {
                              counts[nd] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 69968) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70007) {
                          if (ch < 70004) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70006) {
                              counts[po] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 70018) {
                            if (ch < 70016) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 70019) {
                              counts[mc] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70162) {
                      if (ch < 70094) {
                        if (ch < 70081) {
                          if (ch < 70070) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 70079) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 70089) {
                            if (ch < 70085) {
                              counts[lo] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          } else {
                            if (ch < 70093) {
                              counts[unknown] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70107) {
                          if (ch < 70096) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 70106) {
                              counts[nd] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 70133) {
                            if (ch < 70113) {
                              counts[unknown] += 1;
                            } else {
                              counts[no] += 1;
                            }
                          } else {
                            if (ch < 70144) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70198) {
                        if (ch < 70191) {
                          if (ch < 70163) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 70188) {
                              counts[lo] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 70196) {
                            if (ch < 70194) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 70197) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70320) {
                          if (ch < 70200) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70206) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 70368) {
                            if (ch < 70367) {
                              counts[lo] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 70371) {
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
              }
            }
          } else {
            if (ch < 120123) {
              if (ch < 92784) {
                if (ch < 71090) {
                  if (ch < 70478) {
                    if (ch < 70449) {
                      if (ch < 70405) {
                        if (ch < 70401) {
                          if (ch < 70384) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 70394) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 70402) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70404) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70417) {
                          if (ch < 70413) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70415) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 70441) {
                            if (ch < 70419) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 70442) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70462) {
                        if (ch < 70453) {
                          if (ch < 70450) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 70452) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 70460) {
                            if (ch < 70458) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 70461) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70469) {
                          if (ch < 70464) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 70465) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 70473) {
                            if (ch < 70471) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 70475) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70841) {
                      if (ch < 70502) {
                        if (ch < 70493) {
                          if (ch < 70487) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 70488) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 70498) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 70500) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70517) {
                          if (ch < 70509) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 70512) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        } else {
                          if (ch < 70832) {
                            if (ch < 70784) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 70835) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 70854) {
                        if (ch < 70847) {
                          if (ch < 70842) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 70843) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 70850) {
                            if (ch < 70849) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 70852) {
                              counts[mn] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 70864) {
                          if (ch < 70855) {
                            counts[po] += 1;
                          } else {
                            if (ch < 70856) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 71040) {
                            if (ch < 70874) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 71087) {
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
                  if (ch < 71351) {
                    if (ch < 71230) {
                      if (ch < 71105) {
                        if (ch < 71100) {
                          if (ch < 71094) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 71096) {
                              counts[unknown] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 71102) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 71103) {
                              counts[mc] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71216) {
                          if (ch < 71114) {
                            counts[po] += 1;
                          } else {
                            if (ch < 71168) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
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
                              counts[mn] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 71296) {
                        if (ch < 71236) {
                          if (ch < 71231) {
                            counts[mc] += 1;
                          } else {
                            if (ch < 71233) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 71248) {
                            if (ch < 71237) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 71258) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71341) {
                          if (ch < 71339) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 71340) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        } else {
                          if (ch < 71344) {
                            if (ch < 71342) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          } else {
                            if (ch < 71350) {
                              counts[mn] += 1;
                            } else {
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 74649) {
                      if (ch < 71914) {
                        if (ch < 71370) {
                          if (ch < 71352) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 71360) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        } else {
                          if (ch < 71872) {
                            if (ch < 71840) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 71904) {
                              counts[ll] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 71936) {
                          if (ch < 71923) {
                            counts[no] += 1;
                          } else {
                            if (ch < 71935) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 72441) {
                            if (ch < 72384) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 73728) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 92160) {
                        if (ch < 74864) {
                          if (ch < 74752) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 74863) {
                              counts[nl] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 77824) {
                            if (ch < 74869) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 78895) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 92767) {
                          if (ch < 92729) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 92736) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 92778) {
                            if (ch < 92768) {
                              counts[unknown] += 1;
                            } else {
                              counts[nd] += 1;
                            }
                          } else {
                            if (ch < 92782) {
                              counts[unknown] += 1;
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
                if (ch < 119155) {
                  if (ch < 94095) {
                    if (ch < 92998) {
                      if (ch < 92928) {
                        if (ch < 92912) {
                          if (ch < 92880) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 92910) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 92917) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 92918) {
                              counts[po] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 92988) {
                          if (ch < 92976) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 92983) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 92996) {
                            if (ch < 92992) {
                              counts[so] += 1;
                            } else {
                              counts[lm] += 1;
                            }
                          } else {
                            if (ch < 92997) {
                              counts[po] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 93053) {
                        if (ch < 93019) {
                          if (ch < 93008) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 93018) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 93027) {
                            if (ch < 93026) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 93048) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 94021) {
                          if (ch < 93072) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 93952) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 94033) {
                            if (ch < 94032) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 94079) {
                              counts[mc] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 113820) {
                      if (ch < 113771) {
                        if (ch < 110592) {
                          if (ch < 94099) {
                            counts[mn] += 1;
                          } else {
                            if (ch < 94112) {
                              counts[lm] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 110594) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 113664) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 113792) {
                          if (ch < 113776) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 113789) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 113808) {
                            if (ch < 113801) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 113818) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 119040) {
                        if (ch < 113824) {
                          if (ch < 113821) {
                            counts[so] += 1;
                          } else {
                            if (ch < 113823) {
                              counts[mn] += 1;
                            } else {
                              counts[po] += 1;
                            }
                          }
                        } else {
                          if (ch < 118784) {
                            if (ch < 113828) {
                              counts[cf] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 119030) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 119141) {
                          if (ch < 119079) {
                            counts[so] += 1;
                          } else {
                            if (ch < 119081) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
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
                              counts[mc] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 119968) {
                    if (ch < 119639) {
                      if (ch < 119214) {
                        if (ch < 119173) {
                          if (ch < 119163) {
                            counts[cf] += 1;
                          } else {
                            if (ch < 119171) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
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
                      } else {
                        if (ch < 119362) {
                          if (ch < 119262) {
                            counts[so] += 1;
                          } else {
                            if (ch < 119296) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 119366) {
                            if (ch < 119365) {
                              counts[mn] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 119552) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 119893) {
                        if (ch < 119808) {
                          if (ch < 119648) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 119666) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 119860) {
                            if (ch < 119834) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 119886) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 119938) {
                          if (ch < 119894) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 119912) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 119965) {
                            if (ch < 119964) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 119966) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 120005) {
                      if (ch < 119982) {
                        if (ch < 119973) {
                          if (ch < 119970) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 119971) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 119977) {
                            if (ch < 119975) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 119981) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 119995) {
                          if (ch < 119990) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 119994) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 119997) {
                            if (ch < 119996) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 120004) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 120077) {
                        if (ch < 120068) {
                          if (ch < 120016) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120042) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 120071) {
                            if (ch < 120070) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 120075) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120093) {
                          if (ch < 120085) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120086) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 120120) {
                            if (ch < 120094) {
                              counts[unknown] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 120122) {
                              counts[lu] += 1;
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
              if (ch < 126585) {
                if (ch < 125127) {
                  if (ch < 120546) {
                    if (ch < 120276) {
                      if (ch < 120138) {
                        if (ch < 120133) {
                          if (ch < 120127) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120128) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 120134) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 120135) {
                              counts[lu] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120172) {
                          if (ch < 120145) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120146) {
                              counts[unknown] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 120224) {
                            if (ch < 120198) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 120250) {
                              counts[lu] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 120458) {
                        if (ch < 120354) {
                          if (ch < 120302) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120328) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
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
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120513) {
                          if (ch < 120486) {
                            counts[ll] += 1;
                          } else {
                            if (ch < 120488) {
                              counts[unknown] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 120539) {
                            if (ch < 120514) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          } else {
                            if (ch < 120540) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 120713) {
                      if (ch < 120629) {
                        if (ch < 120597) {
                          if (ch < 120571) {
                            counts[lu] += 1;
                          } else {
                            if (ch < 120572) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        } else {
                          if (ch < 120598) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 120604) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 120656) {
                          if (ch < 120630) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 120655) {
                              counts[ll] += 1;
                            } else {
                              counts[sm] += 1;
                            }
                          }
                        } else {
                          if (ch < 120687) {
                            if (ch < 120662) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          } else {
                            if (ch < 120688) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 120778) {
                        if (ch < 120745) {
                          if (ch < 120714) {
                            counts[sm] += 1;
                          } else {
                            if (ch < 120720) {
                              counts[ll] += 1;
                            } else {
                              counts[lu] += 1;
                            }
                          }
                        } else {
                          if (ch < 120771) {
                            if (ch < 120746) {
                              counts[sm] += 1;
                            } else {
                              counts[ll] += 1;
                            }
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
                            if (ch < 120780) {
                              counts[ll] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 124928) {
                            if (ch < 120832) {
                              counts[nd] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 125125) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 126539) {
                    if (ch < 126505) {
                      if (ch < 126496) {
                        if (ch < 126464) {
                          if (ch < 125136) {
                            counts[no] += 1;
                          } else {
                            if (ch < 125143) {
                              counts[mn] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 126468) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 126469) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 126500) {
                          if (ch < 126497) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 126499) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 126503) {
                            if (ch < 126501) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 126504) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 126524) {
                        if (ch < 126520) {
                          if (ch < 126515) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 126516) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 126522) {
                            if (ch < 126521) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 126523) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 126535) {
                          if (ch < 126530) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 126531) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 126537) {
                            if (ch < 126536) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 126538) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126557) {
                      if (ch < 126549) {
                        if (ch < 126544) {
                          if (ch < 126540) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 126541) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 126547) {
                            if (ch < 126545) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 126548) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 126553) {
                          if (ch < 126551) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 126552) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 126555) {
                            if (ch < 126554) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 126556) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 126565) {
                        if (ch < 126560) {
                          if (ch < 126558) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 126559) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 126563) {
                            if (ch < 126561) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 126564) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 126572) {
                          if (ch < 126567) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 126571) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 126580) {
                            if (ch < 126579) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 126584) {
                              counts[lo] += 1;
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
                if (ch < 128331) {
                  if (ch < 127222) {
                    if (ch < 126652) {
                      if (ch < 126603) {
                        if (ch < 126591) {
                          if (ch < 126589) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 126590) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 126592) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 126602) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 126628) {
                          if (ch < 126620) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 126625) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 126634) {
                            if (ch < 126629) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 126635) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 127136) {
                        if (ch < 126976) {
                          if (ch < 126704) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 126706) {
                              counts[sm] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 127024) {
                            if (ch < 127020) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 127124) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 127168) {
                          if (ch < 127151) {
                            counts[so] += 1;
                          } else {
                            if (ch < 127153) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 127184) {
                            if (ch < 127169) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 127185) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 127561) {
                      if (ch < 127344) {
                        if (ch < 127248) {
                          if (ch < 127232) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 127245) {
                              counts[no] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 127280) {
                            if (ch < 127279) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 127340) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 127491) {
                          if (ch < 127387) {
                            counts[so] += 1;
                          } else {
                            if (ch < 127462) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 127547) {
                            if (ch < 127504) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 127552) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 127872) {
                        if (ch < 127744) {
                          if (ch < 127568) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 127570) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 127792) {
                            if (ch < 127789) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 127870) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 127992) {
                          if (ch < 127951) {
                            counts[so] += 1;
                          } else {
                            if (ch < 127956) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 128255) {
                            if (ch < 128000) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 128256) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 131072) {
                    if (ch < 128768) {
                      if (ch < 128579) {
                        if (ch < 128379) {
                          if (ch < 128336) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 128378) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 128420) {
                            counts[so] += 1;
                          } else {
                            if (ch < 128421) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 128736) {
                          if (ch < 128581) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 128720) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 128752) {
                            if (ch < 128749) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 128756) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 129096) {
                        if (ch < 128981) {
                          if (ch < 128884) {
                            counts[so] += 1;
                          } else {
                            if (ch < 128896) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        } else {
                          if (ch < 129036) {
                            if (ch < 129024) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          } else {
                            if (ch < 129040) {
                              counts[unknown] += 1;
                            } else {
                              counts[so] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 129120) {
                          if (ch < 129104) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 129114) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 129168) {
                            if (ch < 129160) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 129198) {
                              counts[so] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 917505) {
                      if (ch < 177973) {
                        if (ch < 173783) {
                          if (ch < 131073) {
                            counts[lo] += 1;
                          } else {
                            if (ch < 173782) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        } else {
                          if (ch < 173825) {
                            if (ch < 173824) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          } else {
                            if (ch < 177972) {
                              counts[unknown] += 1;
                            } else {
                              counts[lo] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 178205) {
                          if (ch < 177984) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 177985) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 194560) {
                            if (ch < 178206) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          } else {
                            if (ch < 195102) {
                              counts[lo] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        }
                      }
                    } else {
                      if (ch < 983041) {
                        if (ch < 917632) {
                          if (ch < 917506) {
                            counts[cf] += 1;
                          } else {
                            if (ch < 917536) {
                              counts[unknown] += 1;
                            } else {
                              counts[cf] += 1;
                            }
                          }
                        } else {
                          if (ch < 918000) {
                            if (ch < 917760) {
                              counts[unknown] += 1;
                            } else {
                              counts[mn] += 1;
                            }
                          } else {
                            if (ch < 983040) {
                              counts[unknown] += 1;
                            } else {
                              counts[co] += 1;
                            }
                          }
                        }
                      } else {
                        if (ch < 1048576) {
                          if (ch < 1048573) {
                            counts[unknown] += 1;
                          } else {
                            if (ch < 1048574) {
                              counts[co] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
                          }
                        } else {
                          if (ch < 1114109) {
                            if (ch < 1048577) {
                              counts[co] += 1;
                            } else {
                              counts[unknown] += 1;
                            }
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
      printf("%lu\t%s\n", counts[i], categories[i]);
    }
  }

  if (ferror(stdin)) {
    perror("error reading from standard input: ");
    return 1;
  }
  return 0;
}
