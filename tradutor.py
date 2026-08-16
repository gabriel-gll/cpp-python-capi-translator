# tradutor.py
import requests # requests → usada para fazer requisições HTTP, ou seja, acessar APIs pela internet. Aqui ela acessa a API MyMemory para traduzir textos.
from langdetect import detect_langs # biblioteca que detecta idioma automaticamente analisando o texto
from langdetect import DetectorFactory
DetectorFactory.seed = 0


# 🔵 Mapeamento ISO → Nome legível
LANG_NAMES = {
    "af": "Africâner", "ar": "Árabe", "bg": "Búlgaro", "bn": "Bengali",     #É um mapeamento de código ISO (ex: "en", "pt", "es") → nome legível do idioma
    "ca": "Catalão", "cs": "Tcheco", "cy": "Galês", "da": "Dinamarquês",    #Serve para exibir idiomas com o nome completo.
    "de": "Alemão", "el": "Grego", "en": "Inglês", "es": "Espanhol",
    "et": "Estoniano", "fa": "Persa", "fi": "Finlandês", "fr": "Francês",
    "gu": "Gujarati", "he": "Hebraico", "hi": "Hindi", "hr": "Croata",
    "hu": "Húngaro", "id": "Indonésio", "it": "Italiano", "ja": "Japonês",
    "kn": "Kannada", "ko": "Coreano", "lt": "Lituano", "lv": "Letão",
    "mk": "Macedônio", "ml": "Malaiala", "mr": "Marati", "ne": "Nepalês",
    "nl": "Holandês", "no": "Norueguês", "pa": "Punjabi", "pl": "Polonês",
    "pt": "Português", "ro": "Romeno", "ru": "Russo", "sk": "Eslovaco",
    "sl": "Esloveno", "so": "Somali", "sq": "Albanês", "sv": "Sueco",
    "sw": "Suaili", "ta": "Tâmil", "te": "Telugu", "th": "Tailandês",
    "tl": "Tagalog", "tr": "Turco", "uk": "Ucraniano", "ur": "Urdu",
    "vi": "Vietnamita", "zh-cn": "Chinês Simplificado", 
    "zh-tw": "Chinês Tradicional",
}

def language_fullname(code):    #Recebe um código ISO de idioma ("en", "fr", "pt"), procura no dicionário, Se existir → retorna “Inglês”, “Francês”, etc.
    return LANG_NAMES.get(code.lower(), f"Desconhecido ({code})")



# 🟦 Função: detectar idioma
def detect_language(text):
    try:
        if len(text.strip()) < 7:   #Garante que o texto é grande o suficiente, textos muito curtos podem confundir a biblioteca
            return "Texto muito curto para detecção confiável."

        langs = detect_langs(text)  #retorna uma lista de possíveis idiomas, com porcentagem
        best = langs[0] #o idioma mais provável

        nome = language_fullname(best.lang) 
        return f"{nome} ({best.lang}) — confiança {best.prob:.2f}"  #Formata a resposta assim: Inglês (en) — confiança 0.99

    except Exception as e:  #Tratamento de erro, se der problema, não quebra o programa. Retorna mensagem de erro em texto
        return f"Erro na detecção: {str(e)}"



# 🟩 Função responsável por traduzir texto usando a API MyMemory
def translate_text(text, target_lang):
    try:
        
        langs = detect_langs(text)  # Antes de traduzir, detectamos o idioma automaticamente
        src = langs[0].lang  # idioma detectado ISO

        url = "https://api.mymemory.translated.net/get"
        params = {
            "q": text,  #"q" → texto a ser traduzido
            "langpair": f"{src}|{target_lang}"  #"langpair" → idioma_origem | idioma_destino, ex.: "pt|en"
        }

        response = requests.get(url, params=params) #Envia a requisição para a API, Quando você chama a API MyMemory, ela devolve uma resposta no formato JSON.
        data = response.json()  #Converte o JSON retornado para um dicionário Python

        # A tradução vem aqui:
        traduzido = data["responseData"]["translatedText"]  #o MyMemory API devolve várias informações, não só a tradução. Mas a tradução está sempre dentro de responseData["translatedText"]

        return traduzido    #retorna para o C++

    except Exception as e:  #Tratamento de erro, se der problema, não quebra o programa. Retorna mensagem de erro em texto
        return f"Erro na tradução: {str(e)}"


# 🟦 Função: listar idiomas disponíveis
def listar_idiomas():                       #Percorre o dicionário de idiomas
    linhas = []                             #Monta listas de linhas como:
    for codigo, nome in LANG_NAMES.items(): #en — Inglês; es — Espanhol; fr — Francês; pt — Português
        linhas.append(f"{codigo} — {nome}") 
    return "\n".join(linhas)                #junta todas as linhas da lista, separadas por uma quebra de linha (\n)
                                            
