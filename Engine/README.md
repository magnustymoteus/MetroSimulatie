## Gequoteerde functionaliteit

V: Werkend  
-: Deels werkend met gekende problemen (onderaan beschreven)  
X: Niet werkend of niet geïmplementeerd  
(blanco): TODO  


|   | Functionaliteit      | Status |
|---|---------------------------|--------|
| 1 | 2D L-systemen             | V      |
|   | Met haakjes               | V      |
|   | Stochastisch              | V      |
| 2 | Transformaties            | V      |
|   | Eye-point                 | V      |
|   | Projectie                 | V      |
| 3 | Platonische Lichamen      | V      |
|   | Kegel en cylinder         | V      |
|   | Bol                       | V      |
|   | Torus                     | V      |
|   | 3D L-systemen             | V      |
| 4 | Z-buffering (lijnen)      | V      |
| 5 | Triangulatie              | V      |
|   | Z-buffering (driehoeken)  | V      |
| 6 | 3D fractalen              | V      |
|   | BuckyBall                 | X      |
|   | Mengerspons               | X      |
|   | View Frustum              | X      |
| 7 | Ambient licht             | V      |
|   | Diffuus licht (oneindig)  | V      |
|   | Diffuus licht (puntbron)  | V      |
|   | Speculair licht           | V      |
| 8 | Schaduw                   | V      |
|   | Texture mapping           | V      |
| 9 | Bollen en cylinders       | V      |
|   | UV-coordinaten            | V      |
|   | Cube mapping              | V      |

Geïmplementeerde vorm van texture mapping: willekeurige oppervlakken

## Gekende problemen 
- Cube mapping: Texturen worden geprojecteerd, maar het moment van overgang van de ene naar de andere is zichtbaar.

## Extra functionaliteit, niet in de opgaves beschreven
- Bollen en cylinders werken ook met fractalen

## Extra ini's
Alle extra ini bestanden bevinden zich in de map Extra_Tests.
- Extra_Tests/Stochastische_test: hetzelfde 2LD-bestand wordt 3 keer gebruikt.
- Extra_Tests/texture_mapping: 4 voorbeelden van texture mapping op willekeurige oppervlakken.
- Extra_Tests/texture_coordinates: 2 voorbeelden van input van uv-coördinaten.
- Extra_Tests/normal_vectors: 3 voorbeelden met en zonder input van normaalvectoren
- Extra_Tests/cube_mapping: 3 voorbeelden van cube_mapping (cubemapping_debug.ini is om te ziet of alle vlakken van de kubus juist georiënteerd zijn)

