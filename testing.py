import pygame

def worldToScreenPosition(position, cameraPos, cameraZoom):
    return (position - cameraPos - pygame.math.Vector2(400,400)) / cameraZoom + pygame.math.Vector2(400,400)


def screenToWorldPosition(position, cameraPos, cameraZoom):
    return ( position - pygame.math.Vector2(400,400) ) * cameraZoom + cameraPos +  pygame.math.Vector2(400,400)

class Entity:
    def __init__(self, positon: pygame.math.Vector2, dimensions: pygame.math.Vector2, color) -> None:
        self.position = pygame.math.Vector2(positon)
        self.dimensions = pygame.math.Vector2(dimensions)
        self.color = color

    def isSelected( self, screenPosition, cameraPos, cameraZoom ):    
        worldPosition = screenToWorldPosition(pygame.math.Vector2(screenPosition), cameraPos, cameraZoom)
        return self.position.x <= worldPosition.x and worldPosition.x <= self.position.x + self.dimensions.x and self.position.y <= worldPosition.y and worldPosition.y <= self.position.y + self.dimensions.y


    def draw(self, screen: pygame.Surface, cameraPos: pygame.math.Vector2, cameraZoom):
        rect = pygame.Rect(worldToScreenPosition(self.position,cameraPos,cameraZoom), self.dimensions/cameraZoom)
        isSelected = self.isSelected(pygame.mouse.get_pos(), cameraPos, cameraZoom)
        if isSelected:
            self.color = (0,255,0)
        else:
            self.color = (255,255,255)
        pygame.draw.rect(screen,  self.color, rect)


pygame.init()
screen = pygame.display.set_mode( (800,800) )
cameraPos = pygame.math.Vector2(0,0)
cameraZoom = 1
entities = []
entities.append( Entity((100,100), (100,100), (255,0,0)) )
entities.append( Entity((200,100), (100,100), (0,255,0)) )

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
        
    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
        cameraPos.y -= 10
    if keys[pygame.K_s]:
        cameraPos.y += 10
    if keys[pygame.K_a]:
        cameraPos.x -= 10
    if keys[pygame.K_d]:
        cameraPos.x += 10
    if keys[pygame.K_MINUS]:
        cameraZoom -= 0.01
    if keys[pygame.K_EQUALS]:
        cameraZoom += 0.01

    screen.fill( (0,0,0) )

    for entity in entities:
        entity.draw(screen, cameraPos, cameraZoom)

    pygame.display.update()