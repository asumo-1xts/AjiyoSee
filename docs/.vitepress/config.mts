import { defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  lang: 'ja',
  title: 'AjiyoSee',
  description: 'あじよしの現在の営業状況',
  themeConfig: {
    socialLinks: [
      { icon: 'github', link: 'https://github.com/asumo-1xts/AjiyoSee' }
    ]
  },
  head: [
    ['link', { rel: 'icon', href: './favicon.ico' }],
    ['meta', { property: 'og:author', content: 'aSumo' }],
    [
      'meta',
      {
        property: 'og:image',
        content:
          'https://github.com/asumo-1xts/AjiyoSee/blob/main/docs/public/ogp.jpg?raw=true'
      }
    ],
    ['meta', { property: 'og:locale', content: 'ja_JP' }],
    ['meta', { property: 'og:type', content: 'website' }],
    ['meta', { property: 'og:site_name', content: 'AjiyoSee' }],
    ['meta', { property: 'twitter:card', content: 'summary' }],
    ['meta', { property: 'twitter:site', content: '@ajiyoshiver2' }],
    [
      'meta',
      {
        name: 'google-site-verification',
        content: 'dCBfkFCsmVT1nO1EyrXm82-YmZYq7kCApA6fu7WYJEs'
      }
    ]
  ]
})
