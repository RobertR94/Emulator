#pragma once

/* Coderitter: Das hätte auch noch eine Klasse sein können. Diese Variablen werden dann
zu globalen Variablen wo es dann manchmal schwierig wird nachzuvollziehen, wo die überall
ihr Unwesen treiben. Der Programmfluss und die Abhängigkeiten werden dadurch schwieriger zu
verstehen. */
const short size = 256;
const short bound = 127 ;
extern unsigned char memory[256];
