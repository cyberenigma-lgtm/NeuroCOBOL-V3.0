# -*- coding: utf-8 -*-
"""
🌐 NEUROCOBOL V3.0 -- REST API SERVER & MICROSERVICE BRIDGE
Ubicación: HERRAMIENTAS/neurocobol_api_server.py
Autor: cyberenigma-lgtm (Noxferion) (Noxferion) -- AI Systems Architect

Expone una interfaz REST API sobre HTTP para compilar, transpilar COBOL legacy,
validar firmas de autoridad CYEN (0x4359454E) y ejecutar transacciones BCD.
"""

import os
import sys
import json
from flask import Flask, request, jsonify

# Agregar ruta raíz para importar el puente
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
if BASE_DIR not in sys.path:
    sys.path.insert(0, BASE_DIR)

from legacy_cobol_bridge import LegacyCOBOLBridge

app = Flask(__name__)
bridge = LegacyCOBOLBridge()

AUTHORITY_SEAL = "0x4359454E"

@app.route("/api/neurocobol/health", methods=["GET"])
def health_check():
    return jsonify({
        "status": "ONLINE",
        "system": "NeuroCOBOL V3.0 Microservice Bridge",
        "authority_seal": AUTHORITY_SEAL,
        "author": "cyberenigma-lgtm (Noxferion) (Noxferion)",
        "safe_creative_id": "2609217054592",
        "safe_creative_url": "https://www.safecreative.org/work/2609217054592-neurocobol-v3-0-lenguaje-de-orquestacion-cognitiva-compilador-y-runtime-soberano",
        "ip_registration": "00765-02939466"
    })

@app.route("/api/neurocobol/transpile-legacy", methods=["POST"])
def transpile_legacy():
    data = request.get_json(force=True, silent=True) or {}
    legacy_code = data.get("code", "")
    
    if not legacy_code:
        return jsonify({"ok": False, "error": "No se proporcionó código legacy COBOL"}), 400
        
    neuro_code = bridge.transpile_copybook(legacy_code)
    return jsonify({
        "ok": True,
        "input_legacy": legacy_code,
        "output_neurocobol": neuro_code,
        "version": bridge.version
    })

@app.route("/api/neurocobol/calculate-comp3", methods=["POST"])
def calculate_comp3():
    data = request.get_json(force=True, silent=True) or {}
    val1 = data.get("val1", "0.00")
    val2 = data.get("val2", "0.00")
    op = data.get("op", "+")
    
    res = bridge.calculate_comp3_bcd(val1, val2, op)
    return jsonify({
        "ok": True,
        "val1": val1,
        "val2": val2,
        "operation": op,
        "result_bcd": str(res),
        "precision": "COMP-3 Exact BCD (18 digits)"
    })

if __name__ == "__main__":
    print(f"🚀 [NEUROCOBOL V3.0] Iniciando Servidor REST API en http://localhost:5050...")
    app.run(host="0.0.0.0", port=5050, debug=False)
