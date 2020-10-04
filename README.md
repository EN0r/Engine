# RdEngine

Current features:

To use the entity component system you can assign components to entities. You'd do this by doing:
`
RdEntity* entity = new RdEntity;
entity->addComponent<COMPONENT>();
`
To access the component later you can do:
`
entity->getComponent<COMPONENT>();
`
Transform:
The transform has the current modifiers:
`
vec2d position
vec2d scale
float rotation
`
boxCollider2D:
The boxCollider2D has the current modifiers:
`
bool drawOutline
`
Most of the boxCollider inherits it's data from the parent entity.
