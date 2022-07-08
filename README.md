# Boids

## BOIDS são particulas programadas
Para responder a três regras, que em conjunto simulam o comportamento de animais que andam em grupos.
Dependendo dos parãmetros, o conjunto pode se comportar de forma distinta.

### Regras

**Separação**: 
As partículas deverão tentar se deslocar para lugares não aglomerados

**Alinhamento**:
As partículas deverão alinhar seu vetor direção para a média do grupo ao seu redor

**Coesão**:
As partículas deverão se mover ao centro de massa do grupo ao seu redor

Essas simples regras que poderão ter pesos diferentes no comportamento individual de cada partícula gera resultados orgânicos e complexos.

Recursos Externos:
Paper descrevendo -> http://www.cs.toronto.edu/~dt/siggraph97-course/cwr87/
Exemplo (Por [Ben Eater](https://www.youtube.com/c/BenEater/videos)) -> https://eater.net/boids
