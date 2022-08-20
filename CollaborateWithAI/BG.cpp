#include "BG.h"

float BG::getPerlinValue(Vector2i pos)
{
	return perlin[pos.x * sqrt(perlin.size()) + pos.y];
}

void BG::Start(Camera& camera)
{
	arr.setPrimitiveType(Quads);
	onPulse = 0;
	Perlin2Df(perlin, log2(BGTiles.x), BGTiles.x, 1.5);
	for (int i = 0; i < BGTiles.x; i++)
	{
		for (int j = 0; j < BGTiles.y; j++)
		{
			Vector2f tileSize = Vector2f(camera.getSize().x / BGTiles.x, camera.getSize().y / BGTiles.y);
			Color color;
			float val = getPerlinValue(Vector2i(i, j));
			color.r = val * (BGSwitchColors[BGswitchIndices[onPulse]].r / 255) * 80;
			color.g = val * (BGSwitchColors[BGswitchIndices[onPulse]].g / 255) * 80;
			color.b = val * (BGSwitchColors[BGswitchIndices[onPulse]].b / 255) * 80;
			arr.append(Vertex(Vector2f(tileSize.x * i, tileSize.y * j), color));
			arr.append(Vertex(Vector2f(tileSize.x * (i + 1), tileSize.y * j), color));
			arr.append(Vertex(Vector2f(tileSize.x * (i + 1), tileSize.y * (j + 1)), color));
			arr.append(Vertex(Vector2f(tileSize.x * i, tileSize.y * (j + 1)), color));
		}
	}

	

	if (VertexBuffer::isAvailable())
	{
		buffer.setPrimitiveType(Quads);
		buffer.setUsage(VertexBuffer::Dynamic);
		buffer.create(arr.getVertexCount());
		buffer.update(&arr[0]);
	}
}

bool BG::Update()
{

	bool musicChanged = 0;
	if (music.getPlayingOffset().asSeconds() > 1)
	{
		if (musicBefore < BGswitchPoints[onPulse] && music.getPlayingOffset().asSeconds() > BGswitchPoints[onPulse])
		{
			onPulse++;
			musicChanged = 1;
		}
	}
	else
	{
		onPulse = 0;
	}

	musicBefore = music.getPlayingOffset().asSeconds();
	offset += TimeManager::getDeltaTime().asSeconds() * 1;
	Color color;
	if (DoNotUpdate)
		return musicChanged;

	for (int i = 0; i < BGTiles.x; i++)
	{
		for (int j = 0; j < BGTiles.y; j++)
		{
			float col1 = getPerlinValue(Vector2i(i, (int)(j + (int)offset) % BGTiles.x));
			float col2 = getPerlinValue(Vector2i(i, (int)(j + ((int)(offset + 1) % BGTiles.x)) % BGTiles.x));

			float timeBetween = offset - (int)offset;
			float DeltaColor = col2 - col1;
			
			float finalColor = col1 + DeltaColor * timeBetween;
			
			color.r = finalColor * (BGSwitchColors[BGswitchIndices[onPulse]].r / 255.0) * 110;
			color.g = finalColor * (BGSwitchColors[BGswitchIndices[onPulse]].g / 255.0) * 110;
			color.b = finalColor * (BGSwitchColors[BGswitchIndices[onPulse]].b / 255.0) * 110;
			arr[(i * BGTiles.y + j) * 4].color = color;
			arr[(i * BGTiles.y + j) * 4 + 1].color = color;
			arr[(i * BGTiles.y + j) * 4 + 2].color = color;
			arr[(i * BGTiles.y + j) * 4 + 3].color = color;
		}
	}
	if (VertexBuffer::isAvailable())
		buffer.update(&arr[0], buffer.getVertexCount(), 0);
	return musicChanged;
}

void BG::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (DoNotUpdate)
		return;
	if (VertexBuffer::isAvailable())
		target.draw(buffer, states);
	else
		target.draw(arr, states);
}
