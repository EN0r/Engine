# RdEngine

#Current features:

To use the entity component system you can assign components to entities. You'd do this by doing:
`
RdEntity* entity = new RdEntity;
entity->addComponent<COMPONENT>();
`
To access the component later you can do:
`
entity->getComponent<COMPONENT>();
`
