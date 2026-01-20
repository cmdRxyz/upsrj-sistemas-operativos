#!/bin/bash
# ==========================================================
# Archivo: scheduler_discovery.sh
# Práctica: Exploración del Scheduler Real en Linux
# Sistema: Ubuntu 22.04
# ==========================================================

# ----------------------------------------------------------
# CONTEXTO
# En esta práctica buscamos el código fuente real del
# scheduler de Linux. Linux no usa FCFS, SJF ni RR literal,
# sino el Completely Fair Scheduler (CFS).
# ----------------------------------------------------------

echo "=============================================="
echo " EXPLORACIÓN DEL SCHEDULER REAL DE LINUX (CFS)"
echo "=============================================="
echo ""

# ----------------------------------------------------------
# PASO 1
# El código del kernel NO vive en /home
# En Ubuntu suele encontrarse en /usr/src
# ----------------------------------------------------------

echo "1) Nos movemos a /usr/src donde vive el kernel"
cd /usr/src || exit
pwd
echo ""

echo "Listando contenido de /usr/src:"
ls
echo ""

# ----------------------------------------------------------
# PASO 2
# Entramos al directorio de los headers del kernel
# Usamos comodín para que funcione en cualquier versión
# ----------------------------------------------------------

echo "2) Entrando al directorio linux-headers"
cd linux-headers-* || exit
pwd
echo ""

echo "Contenido del kernel:"
ls
echo ""

# ----------------------------------------------------------
# PASO 3
# El scheduler vive en kernel/sched
# El archivo principal del CFS es fair.c
# ----------------------------------------------------------

echo "3) Entrando al directorio del scheduler"
cd kernel/sched || exit
pwd
echo ""

echo "Archivos relacionados con planificación:"
ls
echo ""

# ----------------------------------------------------------
# ARCHIVO IMPORTANTE
# fair.c implementa el Completely Fair Scheduler (CFS)
# ----------------------------------------------------------

echo "=============================================="
echo " ARCHIVO DEL SCHEDULER REAL: fair.c"
echo "=============================================="
echo ""

# ----------------------------------------------------------
# PASO 4
# Mostramos el código fuente REAL del scheduler
# ----------------------------------------------------------

cat fair.c

# ----------------------------------------------------------
# EXPLICACIÓN TEÓRICA (COMENTARIOS)
# ----------------------------------------------------------

# ¿Qué archivo se mostró?
# -> kernel/sched/fair.c
# Este archivo implementa el Completely Fair Scheduler

# ¿Qué scheduler implementa?
# -> CFS (Completely Fair Scheduler)
# Busca que TODOS los procesos reciban tiempo de CPU
# de forma justa usando "virtual runtime"

# Conceptos observados en el código:
# - vruntime (tiempo virtual)
# - fairness (justicia)
# - time slices dinámicos

# Relación con algoritmos vistos:
# FCFS: ejecuta en orden de llegada (injusto)
# SJF: ejecuta el proceso más corto (no práctico en tiempo real)
# RR: reparte tiempo fijo a cada proceso

# CFS mejora RR:
# - No usa quantum fijo
# - Usa tiempo virtual para balancear
# - Mantiene equidad real entre procesos

# ----------------------------------------------------------
# PREGUNTA DE REFLEXIÓN
# ----------------------------------------------------------

# ¿Por qué Linux no implementa FCFS, SJF o RR directamente?
#
# Porque esos algoritmos son teóricos y simplificados.
# En un sistema real:
# - No se conoce el tiempo de ejecución (SJF imposible)
# - FCFS genera starvation
# - RR desperdicia CPU con cambios de contexto
#
# CFS es más justo, dinámico y eficiente para sistemas reales.
